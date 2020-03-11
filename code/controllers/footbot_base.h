#ifndef FOOTBOT_BASE_H
#define FOOTBOT_BASE_H

#include <argos3/core/control_interface/ci_controller.h>
#include <argos3/plugins/robots/generic/control_interface/ci_differential_steering_actuator.h>
#include <argos3/plugins/robots/generic/control_interface/ci_leds_actuator.h>
#include <argos3/plugins/robots/generic/control_interface/ci_range_and_bearing_actuator.h>
#include <argos3/plugins/robots/foot-bot/control_interface/ci_footbot_proximity_sensor.h>
#include <argos3/plugins/robots/generic/control_interface/ci_range_and_bearing_sensor.h>

using namespace argos;
using std::string;

class CFootBotBase : public CCI_Controller {

	private:
		// Actuators
		CCI_DifferentialSteeringActuator *differentialSteeringActuator;
		CCI_LEDsActuator *ledsActuator;
		CCI_RangeAndBearingActuator *rangeAndBearingActuator;

		// Sensors
		CCI_FootBotProximitySensor *footBotProximitySensor;
		CCI_RangeAndBearingSensor *rangeAndBearingSensor;

		// Params
		Real velocity;
		CDegrees maxAngleBetweenHeadingAndObstacle;
		Real maxObstacleProximity;
		string ledsColorString;

		// Other attributes
		CRange<CRadians> doNotTurnAngleRange;
		CColor ledsColor;

	public:
		CFootBotBase();

		virtual void Init(TConfigurationNode &t_node);
		virtual void ControlStep();

};

#endif