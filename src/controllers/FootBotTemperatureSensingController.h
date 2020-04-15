#ifndef FOOT_BOT_TEMPERATURE_SENSING_CONTROLLER_H
#define FOOT_BOT_TEMPERATURE_SENSING_CONTROLLER_H

#include "FootBotBaseController.h"
#include <argos3/plugins/robots/foot-bot/control_interface/ci_footbot_motor_ground_sensor.h>
#include "params/VotingStrategyParams.h"

class FootBotTemperatureSensingController : public FootBotBaseController {

	private:
		// Sensors
		CCI_FootBotMotorGroundSensor *footBotMotorGroundSensor;

		// Params
		VotingStrategyParams votingStrategyParams;

		// General variables and constants
		int preferredExitTemperature;
		CColor preferredExitLightColor;
		Real preferredExitDistance;

		// Methods
		void sense();
		void receiveOpinions();
		void transmitOpinion();

	public:
		// Constructors
		FootBotTemperatureSensingController();

		// Getters
		const CColor& getPreferredExitLightColor() const;

		// Simulator methods
		virtual void Init(TConfigurationNode &configurationNode);
		virtual void ControlStep();
		virtual void Reset();

};

#endif