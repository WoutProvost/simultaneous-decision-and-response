#ifndef FOOT_BOT_GATE_GRIPPING_CONTROLLER_H
#define FOOT_BOT_GATE_GRIPPING_CONTROLLER_H

#include "FootBotController.h"
#include <argos3/plugins/robots/foot-bot/control_interface/ci_footbot_gripper_actuator.h>
#include "params/ReactionStrategyParams.h"

class FootBotGateGrippingController : public FootBotController {

	private:
		// Actuators
		CCI_FootBotGripperActuator *footBotGripperActuator;

		// Params
		ReactionStrategyParams reactionStrategyParams;

		// General variables and constants
		CColor actingExitLightColor;
		CColor candidateExitLightColor;
		int candidateExitTicks;

		// Methods
		void listenToDecisions();

	public:
		// Constructors
		FootBotGateGrippingController();

		// Getters
		const CColor& getActingExitLightColor() const;

		// Simulator methods
		virtual void Init(TConfigurationNode &configurationNode);
		virtual void ControlStep();
		virtual void Reset();

};

#endif