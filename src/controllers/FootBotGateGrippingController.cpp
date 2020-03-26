#include "FootBotGateGrippingController.h"

FootBotGateGrippingController::FootBotGateGrippingController() :
	// Call base class method and initialize attributes and set default values
	FootBotBaseController::FootBotBaseController("black") {
}

void FootBotGateGrippingController::Init(TConfigurationNode &configurationNode) {
	// Call base class method
	FootBotBaseController::Init(configurationNode);

	// Get actuators and sensors
	footBotGripperActuator = GetActuator<CCI_FootBotGripperActuator>("footbot_gripper");
}

void FootBotGateGrippingController::ControlStep() {
	// Call base class method
	FootBotBaseController::ControlStep();
}

// Macro that binds this class to an XML tag
REGISTER_CONTROLLER(FootBotGateGrippingController, "footbot_gate_gripping")