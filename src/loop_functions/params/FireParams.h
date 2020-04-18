#ifndef FIRE_PARAMS_H
#define FIRE_PARAMS_H

#include <argos3/core/utility/configuration/argos_configuration.h>

using namespace argos;

class FireParams {

	public:
		// Params
		int sources;
		Real circleRadius;
		bool isDynamic;
		int dynamicIntervalTicks;
		int dynamicTemperatureIncrease;

		// Constructors
		FireParams();

		// Simulator methods
		void setParams(TConfigurationNode &configurationNode);

};

#endif