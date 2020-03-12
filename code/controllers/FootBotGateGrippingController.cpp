#include "FootBotGateGrippingController.h"

FootBotGateGrippingController::FootBotGateGrippingController() :
    footBotGripperActuator(NULL) {
}

void FootBotGateGrippingController::Init(TConfigurationNode &t_node) {
    // Call base class method
    FootBotBaseController::Init(t_node);

    // Get actuators and sensors
    footBotGripperActuator = GetActuator<CCI_FootBotGripperActuator>("footbot_gripper");
}

void FootBotGateGrippingController::ControlStep() {
    // Call base class method
    FootBotBaseController::ControlStep();
}

// Macro that binds this class to an XML tag
REGISTER_CONTROLLER(FootBotGateGrippingController, "footbot_gate_gripping_controller")