#include "FootBotTemperatureSensingController.h"
#include "enums/RABIndex.h"
#include "../loop_functions/FireEvacuationLoopFunctions.h"

FootBotTemperatureSensingController::FootBotTemperatureSensingController() :
	// Call base class method and initialize attributes and set default values
	FootBotBaseController::FootBotBaseController("white", BehaviorState::SENSING),
	preferredExitTemperature(0),
	preferredExitLightColor(CColor::BLACK),
	preferredExitDistance(0.0) {
}

const CColor& FootBotTemperatureSensingController::getPreferredExitLightColor() const {
	return preferredExitLightColor;
}

void FootBotTemperatureSensingController::Init(TConfigurationNode &configurationNode) {
	// Call base class method
	FootBotBaseController::Init(configurationNode);

	// Get actuators and sensors
	footBotMotorGroundSensor = GetSensor<CCI_FootBotMotorGroundSensor>("footbot_motor_ground");
}

void FootBotTemperatureSensingController::ControlStep() {
	// Call base class method
	FootBotBaseController::ControlStep();

	// Execute correct behavior
	switch(behaviorState) {
		case BehaviorState::SENSING: {
			sense();
			break;
		}
	}

	// Transmit this robot's opinion to other robots in its neighbourhood
	transmitOpinion();
}

void FootBotTemperatureSensingController::Reset() {
	// Call base class method
	FootBotBaseController::Reset();

	// Reset the behavior state to its initial state
	behaviorState = BehaviorState::SENSING;

	// Reset the temperature to its initial state
	preferredExitTemperature = 0;

	// Reset the exit preferred to its initial state
	preferredExitLightColor = CColor::BLACK;

	// Reset the distance to this exit to its initial state
	preferredExitDistance = 0.0;
}

void FootBotTemperatureSensingController::sense() {
	// Continue to perform collision avoidance
	roam();

	// Get readings from the motor ground sensor
	const CCI_FootBotMotorGroundSensor::TReadings &readings = footBotMotorGroundSensor->GetReadings();

	// Determine whether a fire is present and what the temperature of that fire is
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
		maxTemperature *= dynamic_cast<FireEvacuationLoopFunctions&>(simulator.GetLoopFunctions()).getHeatMapParams().maxTemperature;
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
					preferredExitLightColor = furthestExitLightColor;
					preferredExitDistance = furthestExitDistance;
					preferredExitTemperature = maxTemperature;
				}
			}
		}
	}
}

void FootBotTemperatureSensingController::transmitOpinion()  {
	// If the robot is not undecided, send its opinion to other robots in its neighbourhood
	if(preferredExitLightColor != CColor::BLACK) {
		rangeAndBearingActuator->SetData(RABIndex::TEMPERATURE, preferredExitTemperature);
		rangeAndBearingActuator->SetData(RABIndex::EXIT_COLOR_CHANNEL_RED, preferredExitLightColor.GetRed());
		rangeAndBearingActuator->SetData(RABIndex::EXIT_COLOR_CHANNEL_GREEN, preferredExitLightColor.GetGreen());
		rangeAndBearingActuator->SetData(RABIndex::EXIT_COLOR_CHANNEL_BLUE, preferredExitLightColor.GetBlue());
		rangeAndBearingActuator->SetData(RABIndex::EXIT_DISTANCE, preferredExitDistance);
	}
}

// Macro that binds this class to an XML tag
REGISTER_CONTROLLER(FootBotTemperatureSensingController, "footbot_temperature_sensing")