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
}

// Macro that binds this class to an XML tag
REGISTER_CONTROLLER(FootBotTemperatureSensingController, "footbot_temperature_sensing")