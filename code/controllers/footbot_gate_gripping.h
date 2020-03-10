#ifndef FOOTBOT_GATE_GRIPPING_H
#define FOOTBOT_GATE_GRIPPING_H

#include "footbot_base.h"
#include <argos3/plugins/robots/foot-bot/control_interface/ci_footbot_gripper_actuator.h>

class CFootBotGateGripping : public CFootBotBase {

	private:
		// Actuators
		CCI_FootBotGripperActuator *footBotGripperActuator;

	public:
		CFootBotGateGripping();

		virtual void Init(TConfigurationNode &t_node);
		virtual void ControlStep();

};

#endif