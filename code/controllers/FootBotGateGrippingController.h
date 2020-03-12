#ifndef FOOT_BOT_GATE_GRIPPING_CONTROLLER_H
#define FOOT_BOT_GATE_GRIPPING_CONTROLLER_H

#include "FootBotBaseController.h"
#include <argos3/plugins/robots/foot-bot/control_interface/ci_footbot_gripper_actuator.h>

class FootBotGateGrippingController : public FootBotBaseController {

	private:
		// Actuators
		CCI_FootBotGripperActuator *footBotGripperActuator;

	public:
		FootBotGateGrippingController();

		virtual void Init(TConfigurationNode &configurationNode);
		virtual void ControlStep();

};

#endif