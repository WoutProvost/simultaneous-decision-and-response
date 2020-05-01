#include "FootBotGateGrippingController.h"
#include "enums/RABIndex.h"

FootBotGateGrippingController::FootBotGateGrippingController() :
	// Call base class method and initialize attributes and set default values
	FootBotController::FootBotController("black"),
	actingExitLightColor(CColor::BLACK) {
}

const CColor& FootBotGateGrippingController::getActingExitLightColor() const {
	return actingExitLightColor;
}

void FootBotGateGrippingController::Init(TConfigurationNode &configurationNode) {
	// Call base class method
	FootBotController::Init(configurationNode);

	// Get actuators and sensors
	footBotGripperActuator = GetActuator<CCI_FootBotGripperActuator>("footbot_gripper");
	
	// Parse the configuration file for params
	try {
		reactionStrategyParams.setParams(GetNode(configurationNode, "reaction_strategy"));
	} catch(CARGoSException &ex) {
	}
}

void FootBotGateGrippingController::ControlStep() {
	// Call base class method
	FootBotController::ControlStep();

	// Receive opinions from temperature sensing robots in this robot's neighbourhood
	receiveOpinions();
}

void FootBotGateGrippingController::Reset() {
	// Call base class method
	FootBotController::Reset();

	// Reset the exit acted upon to its initial state
	actingExitLightColor = CColor::BLACK;
}

void FootBotGateGrippingController::receiveOpinions() {
	// TODO
}

// Macro that binds this class to an XML tag
REGISTER_CONTROLLER(FootBotGateGrippingController, "footbot_gate_gripping")