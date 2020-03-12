#include "CollisionAvoidanceParams.h"

CollisionAvoidanceParams::CollisionAvoidanceParams() :
	maxAngleBetweenHeadingAndObstacle(10.0f),
	maxObstacleProximity(0.5f) {
}

void CollisionAvoidanceParams::setParams(TConfigurationNode &configurationNode) {
	// Parse the configuration file for params
	GetNodeAttributeOrDefault(configurationNode, "max_angle_between_heading_and_obstacle", maxAngleBetweenHeadingAndObstacle, maxAngleBetweenHeadingAndObstacle);
	GetNodeAttributeOrDefault(configurationNode, "max_obstacle_proximity", maxObstacleProximity, maxObstacleProximity);
}