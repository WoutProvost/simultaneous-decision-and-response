#ifndef FOOTBOT_TEMPERATURE_SENSING_H
#define FOOTBOT_TEMPERATURE_SENSING_H

#include "footbot_base.h"

class CFootBotTemperatureSensing : public CFootBotBase {

	public:
		CFootBotTemperatureSensing();

		virtual void Init(TConfigurationNode &t_node);
		virtual void ControlStep();

};

#endif