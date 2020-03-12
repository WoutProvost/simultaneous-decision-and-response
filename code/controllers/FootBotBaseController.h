#ifndef FOOT_BOT_BASE_CONTROLLER_H
#define FOOT_BOT_BASE_CONTROLLER_H

#include "CollisionAvoidanceParams.h"
#include <argos3/core/control_interface/ci_controller.h>
#include <argos3/plugins/robots/generic/control_interface/ci_differential_steering_actuator.h>
#include <argos3/plugins/robots/generic/control_interface/ci_leds_actuator.h>
#include <argos3/plugins/robots/generic/control_interface/ci_range_and_bearing_actuator.h>
#include <argos3/plugins/robots/foot-bot/control_interface/ci_footbot_proximity_sensor.h>
#include <argos3/plugins/robots/generic/control_interface/ci_range_and_bearing_sensor.h>
#include <argos3/plugins/robots/generic/control_interface/ci_colored_blob_omnidirectional_camera_sensor.h>

using namespace argos;

class FootBotBaseController : public CCI_Controller {

	protected:
		// Actuators
		CCI_DifferentialSteeringActuator *differentialSteeringActuator;
		CCI_LEDsActuator *ledsActuator;
		CCI_RangeAndBearingActuator *rangeAndBearingActuator;

		// Sensors
		CCI_FootBotProximitySensor *footBotProximitySensor;
		CCI_RangeAndBearingSensor *rangeAndBearingSensor;
		CCI_ColoredBlobOmnidirectionalCameraSensor *coloredBlobOmnidirectionalCameraSensor;

		// Params
		Real velocity;
		CColor ledsColor;
		CollisionAvoidanceParams collisionAvoidanceParams;

	public:
		FootBotBaseController();

		virtual void Init(TConfigurationNode &configurationNode);
		virtual void ControlStep();
		virtual void Reset();

};

#endif