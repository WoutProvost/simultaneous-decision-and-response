#ifndef LOG_PARAMS_H
#define LOG_PARAMS_H

#include <argos3/core/utility/configuration/argos_configuration.h>

using namespace argos;
using std::string;

class LogParams {

	public:
		// Params
		string file;
		bool disable;

		// Constructors
		LogParams();

		// Simulator methods
		void setParams(TConfigurationNode &configurationNode);

};

#endif