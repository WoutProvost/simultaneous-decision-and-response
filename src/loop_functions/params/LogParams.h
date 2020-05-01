#ifndef LOG_PARAMS_H
#define LOG_PARAMS_H

#include <argos3/core/utility/configuration/argos_configuration.h>

using namespace argos;
using std::string;

class LogParams {

	private:
		// Params
		string file;
		bool disable;

	public:
		// Constructors
		LogParams();

		// Getters
		const string& getFile() const;
		bool getDisable() const;

		// Simulator methods
		void setParams(TConfigurationNode &configurationNode);

};

#endif