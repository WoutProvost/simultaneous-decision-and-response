#include "PlotParams.h"

PlotParams::PlotParams() :
	// Initialize attributes and set default values
	logData(true),
	logFile("../logs/log.csv"),
	showInRealtime(false),
	realtimeInitialXAxisMaxValue(60) {
}

void PlotParams::setParams(TConfigurationNode &configurationNode) {
	// Parse the configuration file for params
	GetNodeAttributeOrDefault(configurationNode, "log_data", logData, logData);
	GetNodeAttributeOrDefault(configurationNode, "log_file", logFile, logFile);
	GetNodeAttributeOrDefault(configurationNode, "show_in_realtime", showInRealtime, showInRealtime);
	GetNodeAttributeOrDefault(configurationNode, "realtime_initial_x_axis_max_value", realtimeInitialXAxisMaxValue, realtimeInitialXAxisMaxValue);
}