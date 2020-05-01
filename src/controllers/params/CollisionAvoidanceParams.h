#ifndef COLLISION_AVOIDANCE_PARAMS_H
#define COLLISION_AVOIDANCE_PARAMS_H

#include <argos3/core/utility/math/angles.h>
#include <argos3/core/utility/configuration/argos_configuration.h>

using namespace argos;

class CollisionAvoidanceParams {

	private:
		// Params
		CDegrees maxAngleBetweenHeadingAndObstacle;
		Real maxObstacleProximity;

	public:
		// Constructors
		CollisionAvoidanceParams();

		// Getters
		const CDegrees& getMaxAngleBetweenHeadingAndObstacle() const;
		Real getMaxObstacleProximity() const;

		// Simulator methods
		void setParams(TConfigurationNode &configurationNode);

};

#endif