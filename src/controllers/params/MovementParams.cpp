#include "MovementParams.h"

MovementParams::MovementParams() :
	// Initialize attributes and set default values	
	maxVelocity(10.0),
	maxHeadingAngleForNoTurn(10.0),
	minHeadingAngleForHardTurn(90.0) {
}

void MovementParams::setParams(TConfigurationNode &configurationNode) {
	// Parse the configuration file for params
	GetNodeAttributeOrDefault(configurationNode, "max_velocity", maxVelocity, maxVelocity);
	GetNodeAttributeOrDefault(configurationNode, "max_heading_angle_for_no_turn", maxHeadingAngleForNoTurn, maxHeadingAngleForNoTurn);
	GetNodeAttributeOrDefault(configurationNode, "min_heading_angle_for_hard_turn", minHeadingAngleForHardTurn, minHeadingAngleForHardTurn);

	// The max heading angle for no turn can't exceed the min heading angle for a hard turn
	if(maxHeadingAngleForNoTurn > minHeadingAngleForHardTurn) {
		maxHeadingAngleForNoTurn = minHeadingAngleForHardTurn;
	}
}