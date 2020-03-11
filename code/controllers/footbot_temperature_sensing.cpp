#include "footbot_temperature_sensing.h"

CFootBotTemperatureSensing::CFootBotTemperatureSensing() :
    footBotLightSensor(NULL) {
}

void CFootBotTemperatureSensing::Init(TConfigurationNode &t_node) {
    // Call base class method
    CFootBotBase::Init(t_node);

    // Get actuators and sensors
    footBotLightSensor = GetSensor<CCI_FootBotLightSensor>("footbot_light");
}

void CFootBotTemperatureSensing::ControlStep() {
    // Call base class method
    CFootBotBase::ControlStep();
}

// Macro that binds this class to an XML tag
REGISTER_CONTROLLER(CFootBotTemperatureSensing, "footbot_temperature_sensing_controller")