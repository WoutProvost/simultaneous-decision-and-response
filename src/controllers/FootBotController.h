#ifndef FOOT_BOT_CONTROLLER_H
#define FOOT_BOT_CONTROLLER_H

#include <argos3/core/control_interface/ci_controller.h>
#include <argos3/plugins/robots/generic/control_interface/ci_differential_steering_actuator.h>
#include <argos3/plugins/robots/generic/control_interface/ci_leds_actuator.h>
#include <argos3/plugins/robots/foot-bot/control_interface/ci_footbot_proximity_sensor.h>
#include <argos3/plugins/robots/generic/control_interface/ci_range_and_bearing_sensor.h>
#include <argos3/plugins/robots/generic/control_interface/ci_colored_blob_omnidirectional_camera_sensor.h>
#include <argos3/plugins/robots/generic/control_interface/ci_positioning_sensor.h>
#include "params/AppearanceParams.h"
#include "params/MovementParams.h"
#include "params/CollisionAvoidanceParams.h"
#include <argos3/core/utility/math/rng.h>
#include "enums/TurnMode.h"
#include "enums/BehaviorState.h"

using namespace argos;
using std::map;

class FootBotController : public CCI_Controller {

	private:
		// Methods
		CVector2 getVectorToExitLight(CColor exitColor);
		CVector2 getCollisionAvoidanceVector();
		CVector2 getRandomTurnDirectionVector();
		void setWheelVelocitiesFromVector(const CVector2 &heading, bool ignoreNoTurn);

	protected:
		// Actuators
		CCI_DifferentialSteeringActuator *differentialSteeringActuator;
		CCI_LEDsActuator *ledsActuator;

		// Sensors
		CCI_FootBotProximitySensor *footBotProximitySensor;
		CCI_RangeAndBearingSensor *rangeAndBearingSensor;
		CCI_ColoredBlobOmnidirectionalCameraSensor *coloredBlobOmnidirectionalCameraSensor;
		CCI_PositioningSensor *positioningSensor;

		// Params
		AppearanceParams appearanceParams;
		MovementParams movementParams;
		CollisionAvoidanceParams collisionAvoidanceParams;

		// Static variables and constants
		static map<uint32_t,bool> ignoredColoredBlobs;

		// General variables and constants
		CRandom::CRNG *random;
		CColor color;
		TurnMode turnMode;
		BehaviorState behaviorState;
		int randomTurnTicks;
		CVector2 randomTurnVector;
		bool coloredBlobOmnidirectionalCameraSensorEnabled;

		// Methods
		CColor getExitLightColorForRobotsToUse(const CColor &color);
		void roam();

	public:
		// Constructors
		FootBotController();

		// Simulator methods
		virtual void Init(TConfigurationNode &configurationNode);
		virtual void ControlStep();
		virtual void Reset();

};

#endif