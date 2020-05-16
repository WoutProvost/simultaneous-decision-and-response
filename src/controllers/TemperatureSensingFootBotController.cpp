#include "TemperatureSensingFootBotController.h"
#include "enums/RABIndex.h"
#include "../loop_functions/FireEvacuationLoopFunctions.h"

using std::max_element;
using std::pair;

TemperatureSensingFootBotController::TemperatureSensingFootBotController() :
	// Call base class method and initialize attributes and set default values
	FootBotController::FootBotController(),
	preferredExitTemperature(0),
	preferredExitLightColor(CColor::BLACK),
	preferredExitDistance(0.0) {
}

const CColor& TemperatureSensingFootBotController::getPreferredExitLightColor() const {
	return preferredExitLightColor;
}

void TemperatureSensingFootBotController::Init(TConfigurationNode &configurationNode) {
	// Call base class method
	FootBotController::Init(configurationNode);

	// Get actuators and sensors
	rangeAndBearingActuator = GetActuator<CCI_RangeAndBearingActuator>("range_and_bearing");
	footBotMotorGroundSensor = GetSensor<CCI_FootBotMotorGroundSensor>("footbot_motor_ground");

	// Parse the configuration file for params
	try {
		decisionStrategyParams.setParams(GetNode(configurationNode, "decision_strategy"));
	} catch(CARGoSException &ex) {
	}
}

void TemperatureSensingFootBotController::ControlStep() {
	// Call base class method
	FootBotController::ControlStep();

	// Formulate opinion using temperature and distance measurements
	sense();

	// Receive opinions from other temperature sensing robots in this robot's neighborhood
	receiveOpinions();

	// Transmit this robot's opinion to other robots in its neighborhood
	transmitOpinion();

	// If the robot is not undecided, lit up all the LEDs in the ring except the beacon with a color that represents the robot's preferred exit
	// The color is slightly different from the exit color so that it won't be detected as an exit
	if(appearanceParams.getDebugShowPreference() && preferredExitLightColor != CColor::BLACK) {
		ledsActuator->SetAllColors(getExitLightColorForRobotsToUse(preferredExitLightColor));
		ledsActuator->SetSingleColor(12, color);
	}
}

void TemperatureSensingFootBotController::Reset() {
	// Call base class method
	FootBotController::Reset();

	// Clear all data that is still in the buffer
	rangeAndBearingActuator->ClearData();

	// Reset the temperature to its initial state
	preferredExitTemperature = 0;

	// Reset the exit preferred to its initial state
	preferredExitLightColor = CColor::BLACK;

	// Reset the distance to this exit to its initial state
	preferredExitDistance = 0.0;
}

void TemperatureSensingFootBotController::sense() {
	// Get readings from the motor ground sensor
	const CCI_FootBotMotorGroundSensor::TReadings &readings = footBotMotorGroundSensor->GetReadings();

	// Determine whether a fire is present and what the temperature of that fire is
	// Only use the maximum temperature of the four ground sensors, since that's the most important one
	bool fireDetected = false;
	Real maxTemperature = -1.0;
	for(size_t reading = 0, size = readings.size(); reading < size; reading++) {
		Real temperature = 1.0 - readings[reading].Value;
		if(temperature > 0.0) {
			fireDetected = true;
		}
		if(temperature > maxTemperature) {
			maxTemperature = temperature;
		}
	}

	// Adjust the measured temperature to fit the original temperature value
	if(fireDetected) {
		maxTemperature *= dynamic_cast<FireEvacuationLoopFunctions&>(CSimulator::GetInstance().GetLoopFunctions()).getHeatMapParams().getMaxTemperature();
	}

	// Enable the resource-intensive colored blob omnidirectional camera sensor when a fire is detected and the sensor is not yet enabled
	if(fireDetected && !coloredBlobOmnidirectionalCameraSensorEnabled) {
		coloredBlobOmnidirectionalCameraSensor->Enable();
		coloredBlobOmnidirectionalCameraSensorEnabled = true;
	}
	// Disable the resource-intensive colored blob omnidirectional camera sensor when no fire is detected and the sensor is not yet disabled
	else if(!fireDetected && coloredBlobOmnidirectionalCameraSensorEnabled) {
		coloredBlobOmnidirectionalCameraSensor->Disable();
		coloredBlobOmnidirectionalCameraSensorEnabled = false;
	}

	// Leaving the colored blob omnidirectional camera sensor on at all times results in a very big performace hit, especially with increasing numbers of robots
	// Therefore it is beneficial to only enable the sensor temporarily when measurements are needed
	// However, it takes one full control step to enable the sensor, so it won't sense any blobs right after enabling it
	// Due to this limitation there is a very slight possibility to miss an important single distance measurement
	// However, this is only a problem when the robot velocity is extremely high, or when the temperature tiles are extremely small
	// Practically the robot only moves very slightly and the temperature tiles are large enough compared to the size of the robot, so this shouldn't be a problem
	if(coloredBlobOmnidirectionalCameraSensorEnabled) {
		// Get readings from the colored blob omnidirectional camera sensor
		const CCI_ColoredBlobOmnidirectionalCameraSensor::SReadings &readings = coloredBlobOmnidirectionalCameraSensor->GetReadings();

		// Choose the exit that is the furthest away from the fire, by measuring the distance to each of the available exits
		if(readings.BlobList.size() != 0) {
			CColor furthestExitLightColor = CColor::BLACK;
			Real furthestExitDistance = -1.0;
			for(size_t blob = 0, size = readings.BlobList.size(); blob < size; blob++) {
				if(!ignoredColoredBlobs[readings.BlobList[blob]->Color]) {
					Real distance = readings.BlobList[blob]->Distance/100;
					if(distance > furthestExitDistance) {
						furthestExitLightColor = readings.BlobList[blob]->Color;
						furthestExitDistance = distance;
					}
				}
			}

			// Determine whether to change this robot's opinion based on the distance to the furthest exit weighted by the measured temperature
			if(furthestExitLightColor != CColor::BLACK) {
				if(maxTemperature * furthestExitDistance > preferredExitTemperature * preferredExitDistance) {
					preferredExitTemperature = maxTemperature;
					preferredExitLightColor = furthestExitLightColor;
					preferredExitDistance = furthestExitDistance;
				}
			}
		}
	}
}

void TemperatureSensingFootBotController::receiveOpinions() {
	// Get readings from the range and bearing sensor
	const CCI_RangeAndBearingSensor::TReadings &readings = rangeAndBearingSensor->GetReadings();

	// Receive opinions from other temperature sensing robots in this robot's neighborhood
	int totalVotes = 0;
	map<uint32_t,int> exitVotes;
	map<uint32_t,CColor> exitColors;
	map<uint32_t,Real> exitQualities;
	CCI_RangeAndBearingSensor::TReadings validReadings;
	for(size_t reading = 0, size = readings.size(); reading < size; reading++) {
		UInt8 temperature = readings[reading].Data[RABIndex::TEMPERATURE];
		if(temperature != 0) {
			UInt8 red = readings[reading].Data[RABIndex::EXIT_COLOR_CHANNEL_RED];
			UInt8 green = readings[reading].Data[RABIndex::EXIT_COLOR_CHANNEL_GREEN];
			UInt8 blue = readings[reading].Data[RABIndex::EXIT_COLOR_CHANNEL_BLUE];
			CColor exitColor = CColor(red, green, blue);
			UInt8 distanceIntegralPart = readings[reading].Data[RABIndex::EXIT_DISTANCE_PART_INTEGRAL];
			UInt8 distanceFractionalPart = readings[reading].Data[RABIndex::EXIT_DISTANCE_PART_FRACTIONAL];
			Real distance = distanceIntegralPart + static_cast<Real>(distanceFractionalPart)/100;

			totalVotes++;
			exitVotes[exitColor]++;
			exitColors[exitColor] = exitColor;
			exitQualities[exitColor] += temperature * distance;
			validReadings.emplace_back(readings[reading]);
		}
	}

	// If the neighboring robots actually have opinions
	// Use the combined data to potentially influence the opinion of the recipient based upon the used voting model
	if(exitVotes.size() != 0) {
		// If the robot is not undecided, add this robot's opinion to the votes
		if(preferredExitLightColor != CColor::BLACK) {
			totalVotes++;
			exitVotes[preferredExitLightColor]++;
			exitColors[preferredExitLightColor] = preferredExitLightColor;
			exitQualities[preferredExitLightColor] += preferredExitTemperature * preferredExitDistance;
		}

		// Calculate average qualities
		for(auto it = exitQualities.begin(), end = exitQualities.end(); it != end; it++) {
			exitQualities[it->first] /= exitVotes[it->first];
		}

		// Plurality voting
		if(decisionStrategyParams.getMode() == "plurality") {
			auto winningVote = max_element(exitVotes.begin(), exitVotes.end(), [](const pair<uint32_t,int> &a, const pair<uint32_t,int> &b)->bool{return a.second < b.second;});
			if(exitVotes.size() == 1 || static_cast<Real>(winningVote->second)/totalVotes > 1.0/exitVotes.size()) {
				updateOpinion(exitColors[winningVote->first], exitQualities[winningVote->first]);
			}
		}
		// Majority voting
		else if(decisionStrategyParams.getMode() == "majority") {
			auto winningVote = max_element(exitVotes.begin(), exitVotes.end(), [](const pair<uint32_t,int> &a, const pair<uint32_t,int> &b)->bool{return a.second < b.second;});
			if(static_cast<Real>(winningVote->second)/totalVotes > 0.5) {
				updateOpinion(exitColors[winningVote->first], exitQualities[winningVote->first]);
			}
		}
		// Best average quality
		else if(decisionStrategyParams.getMode() == "quality") {
			auto winningVote = max_element(exitQualities.begin(), exitQualities.end(), [](const pair<uint32_t,Real> &a, const pair<uint32_t,Real> &b)->bool{return a.second < b.second;});
			if(isQualityPresentAndUnique(&exitQualities, winningVote->second)) {
				updateOpinion(exitColors[winningVote->first], exitQualities[winningVote->first]);
			}
		}
		// Random neighbor (the robot's own opinion is not added to the list of valid readings in this model)
		else if(decisionStrategyParams.getMode() == "random") {
			int randomNeighbor = random->Uniform(CRange<UInt32>(0, validReadings.size())); // Interval is [min,max) i.e. right-open
			UInt8 temperature = validReadings[randomNeighbor].Data[RABIndex::TEMPERATURE];
			UInt8 red = validReadings[randomNeighbor].Data[RABIndex::EXIT_COLOR_CHANNEL_RED];
			UInt8 green = validReadings[randomNeighbor].Data[RABIndex::EXIT_COLOR_CHANNEL_GREEN];
			UInt8 blue = validReadings[randomNeighbor].Data[RABIndex::EXIT_COLOR_CHANNEL_BLUE];
			CColor exitColor = CColor(red, green, blue);
			UInt8 distanceIntegralPart = validReadings[randomNeighbor].Data[RABIndex::EXIT_DISTANCE_PART_INTEGRAL];
			UInt8 distanceFractionalPart = validReadings[randomNeighbor].Data[RABIndex::EXIT_DISTANCE_PART_FRACTIONAL];
			Real distance = distanceIntegralPart + static_cast<Real>(distanceFractionalPart)/100;
			updateOpinion(exitColor, temperature * distance);
		}
	}
}

void TemperatureSensingFootBotController::transmitOpinion() {
	// If the robot is not undecided, send its opinion to other robots in its neighborhood
	if(preferredExitLightColor != CColor::BLACK) {
		rangeAndBearingActuator->SetData(RABIndex::TEMPERATURE, preferredExitTemperature);
		rangeAndBearingActuator->SetData(RABIndex::EXIT_COLOR_CHANNEL_RED, preferredExitLightColor.GetRed());
		rangeAndBearingActuator->SetData(RABIndex::EXIT_COLOR_CHANNEL_GREEN, preferredExitLightColor.GetGreen());
		rangeAndBearingActuator->SetData(RABIndex::EXIT_COLOR_CHANNEL_BLUE, preferredExitLightColor.GetBlue());

		// Divide the distance into an integral and fractional part using only the first 2 decimal digits
		Real distanceIntegralPart;
		Real distanceFractionalPart = modf(preferredExitDistance, &distanceIntegralPart) * 100;
		rangeAndBearingActuator->SetData(RABIndex::EXIT_DISTANCE_PART_INTEGRAL, distanceIntegralPart);
		rangeAndBearingActuator->SetData(RABIndex::EXIT_DISTANCE_PART_FRACTIONAL, distanceFractionalPart);
	}
}

void TemperatureSensingFootBotController::updateOpinion(CColor exitColor, Real quality) {
	// The actual individual values of the temperature and distance don't really matter, since they're only used multiplied together as the quality
	// As long as these 2 variables multiplied together represent the actual quality, their individual values don't matter
	// The transformation below makes sure both variables fit into individual UInt8 variables, which is necessary for communication
	if(quality <= 255) {
		preferredExitTemperature = 1;
	} else {
		preferredExitTemperature = 255;		
	}
	preferredExitLightColor = exitColor;
	preferredExitDistance = quality / preferredExitTemperature;
}

bool TemperatureSensingFootBotController::isQualityPresentAndUnique(const map<uint32_t,Real> *map, Real quality) {
	int count = 0;

	for(auto it = map->begin(), end = map->end(); it != end; it++) {
		if(it->second == quality) {
			count++;
		}
	}

	return count == 1;
}

// Macro that binds this class to an XML tag
REGISTER_CONTROLLER(TemperatureSensingFootBotController, "temperature_sensing_footbot")