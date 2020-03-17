#ifndef MOVEMENT_PARAMS_H
#define MOVEMENT_PARAMS_H

#include <argos3/core/utility/math/angles.h>
#include <argos3/core/utility/configuration/argos_configuration.h>

using namespace argos;

class MovementParams {

	public:
		// Params
		Real maxVelocity;
		CDegrees maxHeadingAngleForNoTurn;
		CDegrees minHeadingAngleForHardTurn;

		MovementParams();

		void setParams(TConfigurationNode &configurationNode);

};

#endif