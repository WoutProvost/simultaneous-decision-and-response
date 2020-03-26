#ifndef FOOT_BOT_TEMPERATURE_SENSING_CONTROLLER_H
#define FOOT_BOT_TEMPERATURE_SENSING_CONTROLLER_H

#include "FootBotBaseController.h"
#include <argos3/plugins/robots/foot-bot/control_interface/ci_footbot_motor_ground_sensor.h>

class FootBotTemperatureSensingController : public FootBotBaseController {

	private:
		// Sensors
		CCI_FootBotMotorGroundSensor *footBotMotorGroundSensor;

	public:
		FootBotTemperatureSensingController();

		virtual void Init(TConfigurationNode &configurationNode);
		virtual void ControlStep();

};

#endif