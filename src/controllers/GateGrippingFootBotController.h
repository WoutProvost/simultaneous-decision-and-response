#ifndef GATE_GRIPPING_FOOT_BOT_CONTROLLER_H
#define GATE_GRIPPING_FOOT_BOT_CONTROLLER_H

#include "FootBotController.h"
#include <argos3/plugins/robots/foot-bot/control_interface/ci_footbot_gripper_actuator.h>
#include "params/ReactionStrategyParams.h"

class GateGrippingFootBotController : public FootBotController {

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
		void executeResponse();

	public:
		// Constructors
		GateGrippingFootBotController();

		// Getters
		const CColor& getActingExitLightColor() const;

		// Simulator methods
		virtual void Init(TConfigurationNode &configurationNode);
		virtual void ControlStep();
		virtual void Reset();

};

#endif