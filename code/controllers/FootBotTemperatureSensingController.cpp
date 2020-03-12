#include "FootBotTemperatureSensingController.h"

FootBotTemperatureSensingController::FootBotTemperatureSensingController() {
}

void FootBotTemperatureSensingController::Init(TConfigurationNode &configurationNode) {
	// Call base class method
	FootBotBaseController::Init(configurationNode);

	// Get actuators and sensors
	footBotLightSensor = GetSensor<CCI_FootBotLightSensor>("footbot_light");
}

void FootBotTemperatureSensingController::ControlStep() {
	// Call base class method
	FootBotBaseController::ControlStep();

	// const CCI_ColoredBlobOmnidirectionalCameraSensor::SReadings &readings = coloredBlobOmnidirectionalCameraSensor->GetReadings();
	// for(size_t blob = 0, size = readings.BlobList.size(); blob < size; blob++) {
	// 	if(readings.BlobList[blob]->Color != CColor::WHITE && readings.BlobList[blob]->Color != CColor::BLACK && readings.BlobList[blob]->Color != CColor::RED) {
	// 		RLOG << "Blob detected: " << readings.BlobList[blob]->Color << std::endl;
	// 	}
	// }

	// if(!fireDetected) {
	// 	const CCI_FootBotLightSensor::TReadings &readings = footBotLightSensor->GetReadings();
	// 	CVector2 accumulator;
	// 	for(size_t reading = 0, size = readings.size(); reading < size; reading++) {
	// 		accumulator += CVector2(readings[reading].Value, readings[reading].Angle);
	// 	}
	// 	if(accumulator.Length() != 0.0f) {
	// 		differentialSteeringActuator->SetLinearVelocity(0.0f, 0.0f);
	// 		ledsColor.Set("red");
	// 		ledsActuator->SetAllColors(ledsColor);
	// 		fireDetected = true;
	// 		RLOG << "Fire detected: " << accumulator.Length() << std::endl;
	// 	}
	// } else {
	// 	differentialSteeringActuator->SetLinearVelocity(0.0f, 0.0f);
	// }
}

// Macro that binds this class to an XML tag
REGISTER_CONTROLLER(FootBotTemperatureSensingController, "footbot_temperature_sensing")