#ifndef MOVEMENT_PARAMS_H
#define MOVEMENT_PARAMS_H

#include <argos3/core/utility/math/angles.h>
#include <argos3/core/utility/configuration/argos_configuration.h>

using namespace argos;

class MovementParams {

	private:
		// Params
		Real maxVelocity;
		CDegrees maxHeadingAngleForNoTurn;
		CDegrees minHeadingAngleForHardTurn;

	public:
		// Constructors
		MovementParams();

		// Getters
		Real getMaxVelocity() const;
		const CDegrees& getMaxHeadingAngleForNoTurn() const;
		const CDegrees& getMinHeadingAngleForHardTurn() const;

		// Simulator methods
		void setParams(TConfigurationNode &configurationNode);

};

#endif