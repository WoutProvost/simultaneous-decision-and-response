#ifndef COLLISION_AVOIDANCE_PARAMS_H
#define COLLISION_AVOIDANCE_PARAMS_H

#include <argos3/core/utility/math/angles.h>
#include <argos3/core/utility/configuration/argos_configuration.h>

using namespace argos;

class CollisionAvoidanceParams {

	public:
		CDegrees maxAngleBetweenHeadingAndObstacle;
		Real maxObstacleProximity;

		CollisionAvoidanceParams();

		void setParams(TConfigurationNode &configurationNode);

};

#endif