#ifndef FOOT_BOT_TEMPERATURE_SENSING_CONTROLLER_H
#define FOOT_BOT_TEMPERATURE_SENSING_CONTROLLER_H

#include "FootBotBaseController.h"

class FootBotTemperatureSensingController : public FootBotBaseController {

	public:
		virtual void Init(TConfigurationNode &configurationNode);
		virtual void ControlStep();

};

#endif