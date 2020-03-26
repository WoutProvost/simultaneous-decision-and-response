#ifndef FIRE_PARAMS_H
#define FIRE_PARAMS_H

#include <argos3/core/utility/configuration/argos_configuration.h>

using namespace argos;
using std::string;

class FireParams {

	public:
		// Params
		string mode;
		Real circleRadius;
		bool isDynamic;
		int dynamicIntervalTicks;
		int dynamicTemperatureIncrease;

		FireParams();

		void setParams(TConfigurationNode &configurationNode);

};

#endif