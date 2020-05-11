#ifndef TEMPERATURE_SENSING_FOOT_BOT_CONTROLLER_H
#define TEMPERATURE_SENSING_FOOT_BOT_CONTROLLER_H

#include "FootBotController.h"
#include <argos3/plugins/robots/generic/control_interface/ci_range_and_bearing_actuator.h>
#include <argos3/plugins/robots/foot-bot/control_interface/ci_footbot_motor_ground_sensor.h>
#include "params/DecisionStrategyParams.h"

class TemperatureSensingFootBotController : public FootBotController {

	private:
		// Actuators
		CCI_RangeAndBearingActuator *rangeAndBearingActuator;
		
		// Sensors
		CCI_FootBotMotorGroundSensor *footBotMotorGroundSensor;

		// Params
		DecisionStrategyParams decisionStrategyParams;

		// General variables and constants
		int preferredExitTemperature;
		CColor preferredExitLightColor;
		Real preferredExitDistance;

		// Methods
		void sense();
		void receiveOpinions();
		void transmitOpinion();
		void updateOpinion(int temperature, CColor exitColor, Real distance, int votes);
		bool isQualityPresentAndUnique(const map<uint32_t,Real> *map, Real quality);

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