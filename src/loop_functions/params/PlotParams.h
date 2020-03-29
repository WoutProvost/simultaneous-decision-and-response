#ifndef PLOT_PARAMS_H
#define PLOT_PARAMS_H

#include <argos3/core/utility/configuration/argos_configuration.h>

using namespace argos;

class PlotParams {

	public:
		// Params
		bool logData;
		bool showInRealtime;
		int realtimeInitialXAxisMaxValue;

		// Constructors
		PlotParams();

		// Simulator methods
		void setParams(TConfigurationNode &configurationNode);

};

#endif