#ifndef TEMPERATURE_SENSING_FOOT_BOT_CONTROLLER_H
#define TEMPERATURE_SENSING_FOOT_BOT_CONTROLLER_H

#include "FootBotController.h"
#include <argos3/plugins/robots/foot-bot/control_interface/ci_footbot_motor_ground_sensor.h>
#include "params/DecisionStrategyParams.h"
#include <argos3/core/utility/math/rng.h>

class TemperatureSensingFootBotController : public FootBotController {

	private:
		// Sensors
		CCI_FootBotMotorGroundSensor *footBotMotorGroundSensor;

		// Params
		DecisionStrategyParams decisionStrategyParams;

		// General variables and constants
		CRandom::CRNG *random;
		int preferredExitTemperature;
		CColor preferredExitLightColor;
		Real preferredExitDistance;

		// Methods
		void sense();
		void receiveOpinions();
		void transmitOpinion();
		void updateOpinion(UInt8 temperature, CColor exitColor, UInt8 distance, int votes);

	public:
		// Constructors
		TemperatureSensingFootBotController();

		// Getters
		const CColor& getPreferredExitLightColor() const;

		// Simulator methods
		virtual void Init(TConfigurationNode &configurationNode);
		virtual void ControlStep();
		virtual void Reset();

};

#endif