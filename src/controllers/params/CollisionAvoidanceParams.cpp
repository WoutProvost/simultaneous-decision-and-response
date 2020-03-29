#include "CollisionAvoidanceParams.h"

CollisionAvoidanceParams::CollisionAvoidanceParams() :
	// Initialize attributes and set default values
	maxAngleBetweenHeadingAndObstacle(5.0),
	maxObstacleProximity(0.1) {
}

void CollisionAvoidanceParams::setParams(TConfigurationNode &configurationNode) {
	// Parse the configuration file for params
	GetNodeAttributeOrDefault(configurationNode, "max_angle_between_heading_and_obstacle", maxAngleBetweenHeadingAndObstacle, maxAngleBetweenHeadingAndObstacle);
	GetNodeAttributeOrDefault(configurationNode, "max_obstacle_proximity", maxObstacleProximity, maxObstacleProximity);
}