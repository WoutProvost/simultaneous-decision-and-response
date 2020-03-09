#ifndef FOOTBOT_TEMPERATURE_SENSING_H
#define FOOTBOT_TEMPERATURE_SENSING_H

#include "../footbot_base/footbot_base.h"
#include <argos3/core/control_interface/ci_controller.h>

using namespace argos;

class CFootBotTemperatureSensing : public CFootBotBase {

	public:
		CFootBotTemperatureSensing();

		virtual void Init(TConfigurationNode& t_node);
		virtual void ControlStep();

};

#endif