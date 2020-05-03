#ifndef APPEARANCE_PARAMS_H
#define APPEARANCE_PARAMS_H

#include <argos3/core/utility/configuration/argos_configuration.h>

using namespace argos;
using std::string;

class AppearanceParams {

	private:
		// Params
		string ledsColor;
		bool debugShowPreference;

	public:
		// Constructors
		AppearanceParams();

		// Getters
		const string& getLedsColor() const;
		bool getDebugShowPreference() const;

		// Simulator methods
		void setParams(TConfigurationNode &configurationNode);

};

#endif