#include "NestParams.h"

NestParams::NestParams() :
	// Initialize attributes and set default values
	size(15, 15) {
}

const CVector2& NestParams::getSize() const {
	return size;
}

void NestParams::setParams(TConfigurationNode &configurationNode) {
	// Parse the configuration file for params
	GetNodeAttributeOrDefault(configurationNode, "size", size, size);
}