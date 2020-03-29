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

	// Enable the colored blob omnidirectional camera sensor
	// coloredBlobOmnidirectionalCameraSensor->Enable();
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

	// const CCI_ColoredBlobOmnidirectionalCameraSensor::SReadings &readings = coloredBlobOmnidirectionalCameraSensor->GetReadings();
	// for(size_t blob = 0, size = readings.BlobList.size(); blob < size; blob++) {
	// 	if(!ignoredColoredBlobs[readings.BlobList[blob]->Color]) {
	// 		RLOG << "Blob: " << readings.BlobList[blob]->Color
	// 			<< " " << ToDegrees(readings.BlobList[blob]->Angle).GetValue() << "°"
	// 			<< " " << readings.BlobList[blob]->Distance/100 << "m"
	// 			<< std::endl;
	// 	}
	// }
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

	// Get readings from the ground sensor
	// const CCI_FootBotMotorGroundSensor::TReadings &readings = footBotMotorGroundSensor->GetReadings();

	// Print out the temperature from each reading
	// for(size_t reading = 0, size = readings.size(); reading < size; reading++) {
	// 	RLOG << readings[reading].Value * maxTemperature << "° ";
	// }
	// RLOG << std::endl;
}

// Macro that binds this class to an XML tag
REGISTER_CONTROLLER(FootBotTemperatureSensingController, "footbot_temperature_sensing")