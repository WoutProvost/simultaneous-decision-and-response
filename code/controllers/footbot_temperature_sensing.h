#ifndef FOOTBOT_TEMPERATURE_SENSING_H
#define FOOTBOT_TEMPERATURE_SENSING_H

#include "footbot_base.h"
#include <argos3/plugins/robots/foot-bot/control_interface/ci_footbot_light_sensor.h>

class CFootBotTemperatureSensing : public CFootBotBase {

	private:
		// Sensors
		CCI_FootBotLightSensor *footBotLightSensor;

	public:
		CFootBotTemperatureSensing();

		virtual void Init(TConfigurationNode &t_node);
		virtual void ControlStep();

};

#endif