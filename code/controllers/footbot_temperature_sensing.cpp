#include "footbot_temperature_sensing.h"

CFootBotTemperatureSensing::CFootBotTemperatureSensing() {
}

void CFootBotTemperatureSensing::Init(TConfigurationNode &t_node) {
    // Call base class method
    CFootBotBase::Init(t_node);
}

void CFootBotTemperatureSensing::ControlStep() {
    // Call base class method
    CFootBotBase::ControlStep();
}

// Macro that binds this class to an XML tag
REGISTER_CONTROLLER(CFootBotTemperatureSensing, "footbot_temperature_sensing_controller")