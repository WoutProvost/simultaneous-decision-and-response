#include "FootBotTemperatureSensingController.h"

FootBotTemperatureSensingController::FootBotTemperatureSensingController() :
    footBotLightSensor(NULL) {
}

void FootBotTemperatureSensingController::Init(TConfigurationNode &t_node) {
    // Call base class method
    FootBotBaseController::Init(t_node);

    // Get actuators and sensors
    footBotLightSensor = GetSensor<CCI_FootBotLightSensor>("footbot_light");
}

void FootBotTemperatureSensingController::ControlStep() {
    // Call base class method
    FootBotBaseController::ControlStep();
}

// Macro that binds this class to an XML tag
REGISTER_CONTROLLER(FootBotTemperatureSensingController, "footbot_temperature_sensing_controller")