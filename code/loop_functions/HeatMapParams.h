#ifndef HEAT_MAP_PARAMS_H
#define HEAT_MAP_PARAMS_H

#include <argos3/core/utility/configuration/argos_configuration.h>

using namespace argos;
using std::string;

// All possible colors of a grayscale gradient sit in the range [0:255]
#define MAX_POSSIBLE_TEMPERATURE		255

class HeatMapParams {

	public:
		// Params
		int tilesPerMeter;
		int maxTemperature;
		string debugMode;
		bool showTemperature;

		HeatMapParams();

		void setParams(TConfigurationNode &configurationNode);

};

#endif