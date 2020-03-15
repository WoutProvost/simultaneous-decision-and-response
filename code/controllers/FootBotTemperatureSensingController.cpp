#include "FootBotTemperatureSensingController.h"

void FootBotTemperatureSensingController::Init(TConfigurationNode &configurationNode) {
	// Call base class method
	FootBotBaseController::Init(configurationNode);

	// Get actuators and sensors
	footBotMotorGroundSensor = GetSensor<CCI_FootBotMotorGroundSensor>("footbot_motor_ground");
}

void FootBotTemperatureSensingController::ControlStep() {
	// Call base class method
	FootBotBaseController::ControlStep();

	// Get readings from the ground sensor
	const CCI_FootBotMotorGroundSensor::TReadings &readings = footBotMotorGroundSensor->GetReadings();

	// Temperature = value * maxTemperature
	// RLOG << "Temperature = " << readings[0].Value * 255 << std::endl;
}

// Macro that binds this class to an XML tag
REGISTER_CONTROLLER(FootBotTemperatureSensingController, "footbot_temperature_sensing")