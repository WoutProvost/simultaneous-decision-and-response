#ifndef FOOTBOT_GATE_GRIPPING_H
#define FOOTBOT_GATE_GRIPPING_H

#include "../footbot_base/footbot_base.h"
#include <argos3/core/control_interface/ci_controller.h>

using namespace argos;

class CFootBotGateGripping : public CFootBotBase {

	public:
		CFootBotGateGripping();

		virtual void Init(TConfigurationNode& t_node);
		virtual void ControlStep();

};

#endif