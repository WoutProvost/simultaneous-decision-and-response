#include "TemperatureSensingFootBotController.h"
#include "enums/RABIndex.h"
#include "../loop_functions/FireEvacuationLoopFunctions.h"

using std::max_element;

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

	// Receive opinions from other temperature sensing robots in this robot's neighbourhood
	receiveOpinions();

	// Transmit this robot's opinion to other robots in its neighbourhood
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
				if(furthestExitDistance * maxTemperature > preferredExitDistance * preferredExitTemperature) {
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

	// Receive opinions from other temperature sensing robots in this robot's neighbourhood
	int totalVotes = 0;
	map<uint32_t,int> exitVotes;
	map<uint32_t,UInt8> exitTemperatures;
	map<uint32_t,CColor> exitColors;
	map<uint32_t,UInt8> exitDistances;
	CCI_RangeAndBearingSensor::TReadings validReadings;
	for(size_t reading = 0, size = readings.size(); reading < size; reading++) {
		UInt8 temperature = readings[reading].Data[RABIndex::TEMPERATURE];
		if(temperature != 0) {
			UInt8 red = readings[reading].Data[RABIndex::EXIT_COLOR_CHANNEL_RED];
			UInt8 green = readings[reading].Data[RABIndex::EXIT_COLOR_CHANNEL_GREEN];
			UInt8 blue = readings[reading].Data[RABIndex::EXIT_COLOR_CHANNEL_BLUE];
			CColor exitColor = CColor(red, green, blue);
			UInt8 distance = readings[reading].Data[RABIndex::EXIT_DISTANCE];

			totalVotes++;
			exitVotes[exitColor]++;
			exitTemperatures[exitColor] += temperature;
			exitColors[exitColor] = exitColor;
			exitDistances[exitColor] += distance;
			validReadings.emplace_back(readings[reading]);
		}
	}

	// If the neighbouring robots actually have opinions
	// Use the combined data to potentially influence the opinion of the recipient based upon the used voting model
	if(exitVotes.size() != 0) {
		// If the robot is not undecided, add this robot's opinion to the votes
		if(preferredExitLightColor != CColor::BLACK) {
			exitVotes[preferredExitLightColor]++;
			exitTemperatures[preferredExitLightColor] += preferredExitTemperature;
			exitColors[preferredExitLightColor] = preferredExitLightColor;
			exitDistances[preferredExitLightColor] += preferredExitDistance;
		}

		// Plurality voting (only use a strict winning vote, i.e. don't do anything when there's an ex aequo for the winning vote)
		if(decisionStrategyParams.getMode() == "plurality") {
			map<uint32_t,int>::iterator winningVote = max_element(exitVotes.begin(), exitVotes.end());
			map<uint32_t,int>::iterator it = exitVotes.begin();
			while(it != exitVotes.end() && (it->second != winningVote->second || it->first == winningVote->first)) {
				it++;
			}
			if(it == exitVotes.end()) {
				updateOpinion(exitTemperatures[winningVote->first], exitColors[winningVote->first], exitDistances[winningVote->first], exitVotes[winningVote->first]);
			}
		}
		// Majority voting
		else if(decisionStrategyParams.getMode() == "majority") {
			map<uint32_t,int>::iterator winningVote = max_element(exitVotes.begin(), exitVotes.end());
			if(static_cast<Real>(winningVote->second)/totalVotes > 0.5) {
				updateOpinion(exitTemperatures[winningVote->first], exitColors[winningVote->first], exitDistances[winningVote->first], exitVotes[winningVote->first]);
			}
		}
		// Random neighbour (the robot's own opinion is not added to the list of valid readings in this model)
		else if(decisionStrategyParams.getMode() == "random") {
			int randomNeighbour = rand() % validReadings.size();
			UInt8 temperature = validReadings[randomNeighbour].Data[RABIndex::TEMPERATURE];
			UInt8 red = validReadings[randomNeighbour].Data[RABIndex::EXIT_COLOR_CHANNEL_RED];
			UInt8 green = validReadings[randomNeighbour].Data[RABIndex::EXIT_COLOR_CHANNEL_GREEN];
			UInt8 blue = validReadings[randomNeighbour].Data[RABIndex::EXIT_COLOR_CHANNEL_BLUE];
			CColor exitColor = CColor(red, green, blue);
			UInt8 distance = validReadings[randomNeighbour].Data[RABIndex::EXIT_DISTANCE];
			updateOpinion(temperature, exitColor, distance, 1);
		}
		// Weighted voter model
		else if(decisionStrategyParams.getMode() == "weighted") {
			// TODO
		}
	}
}

void TemperatureSensingFootBotController::transmitOpinion() {
	// If the robot is not undecided, send its opinion to other robots in its neighbourhood
	if(preferredExitLightColor != CColor::BLACK) {
		rangeAndBearingActuator->SetData(RABIndex::TEMPERATURE, preferredExitTemperature);
		rangeAndBearingActuator->SetData(RABIndex::EXIT_COLOR_CHANNEL_RED, preferredExitLightColor.GetRed());
		rangeAndBearingActuator->SetData(RABIndex::EXIT_COLOR_CHANNEL_GREEN, preferredExitLightColor.GetGreen());
		rangeAndBearingActuator->SetData(RABIndex::EXIT_COLOR_CHANNEL_BLUE, preferredExitLightColor.GetBlue());
		rangeAndBearingActuator->SetData(RABIndex::EXIT_DISTANCE, preferredExitDistance);
	}
}

void TemperatureSensingFootBotController::updateOpinion(UInt8 temperature, CColor exitColor, UInt8 distance, int votes) {
	// The exit, distance and temperature resulting form the voting model, will only be copied by the robot if the measured quality is better than its own measured quality
	if(static_cast<Real>(distance) * temperature / votes > preferredExitDistance * preferredExitTemperature) {
		preferredExitTemperature = static_cast<Real>(temperature) / votes;
		preferredExitLightColor = exitColor;
		preferredExitDistance = static_cast<Real>(distance) / votes;
	}
}

// Macro that binds this class to an XML tag
REGISTER_CONTROLLER(TemperatureSensingFootBotController, "temperature_sensing_footbot")