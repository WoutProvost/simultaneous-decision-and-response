#ifndef DIVIDER_PARAMS_H
#define DIVIDER_PARAMS_H

#include <argos3/core/utility/configuration/argos_configuration.h>

using namespace argos;

class DividerParams {

	private:
		// Params
		bool enable;

	public:
		// Constructors
		DividerParams();

		// Getters
		bool getEnable() const;

		// Simulator methods
		void setParams(TConfigurationNode &configurationNode);

};

#endif