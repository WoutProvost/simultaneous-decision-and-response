#ifndef FOOTBOT_BASE_H
#define FOOTBOT_BASE_H

#include <argos3/core/control_interface/ci_controller.h>
#include <argos3/plugins/robots/generic/control_interface/ci_differential_steering_actuator.h>
#include <argos3/plugins/robots/foot-bot/control_interface/ci_footbot_proximity_sensor.h>

using namespace argos;

class CFootBotBase : public CCI_Controller {

	private:
		// Actuators
		CCI_DifferentialSteeringActuator* m_pcDifferentialSteeringActuator;

		// Sensors
		CCI_FootBotProximitySensor* m_pcProximitySensor;

		// Params
		Real m_fVelocity;
		CDegrees m_cMaxAngleBetweenHeadingAndObstacle;
		Real m_fMaxObstacleProximity;

		// Other attributes
		CRange<CRadians> m_cGoStraightAngleRange;

	public:
		CFootBotBase();

		virtual void Init(TConfigurationNode& t_node);
		virtual void ControlStep();

};

#endif