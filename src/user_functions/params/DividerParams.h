#ifndef DIVIDER_PARAMS_H
#define DIVIDER_PARAMS_H

#include <argos3/core/utility/configuration/argos_configuration.h>

using namespace argos;

class DividerParams {

	private:
		// Params
		bool enableHorizontal;
		bool enableVertical;

	public:
		// Constructors
		DividerParams();

		// Getters
		bool getEnableHorizontal() const;
		bool getEnableVertical() const;

		// Simulator methods
		void setParams(TConfigurationNode &configurationNode);

};

#endif