#ifndef FOOT_BOT_TEMPERATURE_SENSING_CONTROLLER_H
#define FOOT_BOT_TEMPERATURE_SENSING_CONTROLLER_H

#include "FootBotBaseController.h"
#include <argos3/plugins/robots/foot-bot/control_interface/ci_footbot_light_sensor.h>

class FootBotTemperatureSensingController : public FootBotBaseController {

	private:
		// Sensors
		CCI_FootBotLightSensor *footBotLightSensor;

	public:
		FootBotTemperatureSensingController();

		virtual void Init(TConfigurationNode &t_node);
		virtual void ControlStep();

};

#endif