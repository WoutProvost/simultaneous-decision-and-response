#include "FootBotTemperatureSensingController.h"

FootBotTemperatureSensingController::FootBotTemperatureSensingController() :
	// Call base class method and initialize attributes and set default values
	FootBotBaseController::FootBotBaseController("white", BehaviorState::SENSING) {
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
}

void FootBotTemperatureSensingController::Reset() {
	// Call base class method
	FootBotBaseController::Reset();

	// Reset the behavior state to its initial state
	behaviorState = BehaviorState::SENSING;
}

void FootBotTemperatureSensingController::sense() {
	// Continue to perform collision avoidance
	roam();

	// Get readings from the motor ground sensor
	const CCI_FootBotMotorGroundSensor::TReadings &readings = footBotMotorGroundSensor->GetReadings();

	// Determine wether a fire is present and what the temperature of that fire is
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
	
	// Enable the resource-intensive colored blob omnidirectional camera sensor when a fire is detected and the sensor is not yet enabled
	if(fireDetected && !coloredBlobOmnidirectionalCameraSensorEnabled) {
		coloredBlobOmnidirectionalCameraSensor->Enable();
		coloredBlobOmnidirectionalCameraSensorEnabled = true;
	}
	// Disable the resource-intensive colored blob omnidirectional camera sensor when no fire is detected and the sensor is not yet disabled
	else if(!fireDetected && coloredBlobOmnidirectionalCameraSensorEnabled) {
		coloredBlobOmnidirectionalCameraSensor->Disable();
		coloredBlobOmnidirectionalCameraSensorEnabled = false;

		// Clear all data that is still in the buffer
		rangeAndBearingActuator->ClearData();
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
			CColor furthestExitColor;
			Real furthestExitDistance = -1.0;
			for(size_t blob = 0, size = readings.BlobList.size(); blob < size; blob++) {
				if(!ignoredColoredBlobs[readings.BlobList[blob]->Color]) {
					Real distance = readings.BlobList[blob]->Distance/100;
					if(distance > furthestExitDistance) {
						furthestExitColor = readings.BlobList[blob]->Color;
						furthestExitDistance = distance;
					}
				}
			}

			// Send the temperature measured and exit prefered by this robot to other robots in its neighbourhood
			// rangeAndBearingActuator->SetData(RABIndex::TEMPERATURE, maxTemperature * fireEvacuationLoopFunctions.heatMapParams.maxTemperature);
			rangeAndBearingActuator->SetData(RABIndex::EXIT_COLOR_CHANNEL_RED, furthestExitColor.GetRed());
			rangeAndBearingActuator->SetData(RABIndex::EXIT_COLOR_CHANNEL_GREEN, furthestExitColor.GetGreen());
			rangeAndBearingActuator->SetData(RABIndex::EXIT_COLOR_CHANNEL_BLUE, furthestExitColor.GetBlue());
		}
	}
}

// Macro that binds this class to an XML tag
REGISTER_CONTROLLER(FootBotTemperatureSensingController, "footbot_temperature_sensing")