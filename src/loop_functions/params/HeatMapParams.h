#ifndef HEAT_MAP_PARAMS_H
#define HEAT_MAP_PARAMS_H

#include <argos3/core/utility/configuration/argos_configuration.h>

using namespace argos;
using std::string;

// All possible colors of a grayscale gradient sit in the range [0:255]
// The range and bearing sensor can only send data in chunks of 1 byte which holds values in the range [0:255]
#define MAX_POSSIBLE_TEMPERATURE		255

class HeatMapParams {

	public:
		// Params
		int tilesPerMeter;
		int maxTemperature;
		bool showTemperature;
		string debugMode;
		bool debugUseColors;

		// Constructors
		HeatMapParams();

		// Simulator methods
		void setParams(TConfigurationNode &configurationNode);

};

#endif