#include "FootBotBaseController.h"

FootBotBaseController::FootBotBaseController() :
	// Initialize attributes and set default values
	velocity(2.5f),
	ledsColor("black"),
	color(0, 0, 0, 255) {
}

void FootBotBaseController::Init(TConfigurationNode &configurationNode) {
	// Get actuators and sensors
	differentialSteeringActuator = GetActuator<CCI_DifferentialSteeringActuator>("differential_steering");
	ledsActuator = GetActuator<CCI_LEDsActuator>("leds");
	rangeAndBearingActuator = GetActuator<CCI_RangeAndBearingActuator>("range_and_bearing");
	footBotProximitySensor = GetSensor<CCI_FootBotProximitySensor>("footbot_proximity");
	rangeAndBearingSensor = GetSensor<CCI_RangeAndBearingSensor>("range_and_bearing");
	coloredBlobOmnidirectionalCameraSensor = GetSensor<CCI_ColoredBlobOmnidirectionalCameraSensor>("colored_blob_omnidirectional_camera");
	footBotLightSensor = GetSensor<CCI_FootBotLightSensor>("footbot_light");

	// Parse the configuration file for params
	GetNodeAttributeOrDefault(configurationNode, "velocity", velocity, velocity);
	GetNodeAttributeOrDefault(configurationNode, "leds_color", ledsColor, ledsColor);
	collisionAvoidanceParams = CollisionAvoidanceParams();
	try {
		collisionAvoidanceParams.setParams(GetNode(configurationNode, "collision_avoidance"));
	} catch(CARGoSException &ex) {
	}

	// Lit up all the LEDs in the ring with the same color and intensity
	color.Set(ledsColor);
	ledsActuator->SetAllColors(color);

	// Enable the colored blob omnidirectional camera sensor
	// coloredBlobOmnidirectionalCameraSensor->Enable();
}

void FootBotBaseController::ControlStep() {
	// Get readings from the proximity sensor
	const CCI_FootBotProximitySensor::TReadings &readings = footBotProximitySensor->GetReadings();

	// Sum these readings together (vector addition gives a new vector that points directly to the obstacle)
	CVector2 accumulator;
	for(size_t reading = 0, size = readings.size(); reading < size; reading++) {
		accumulator += CVector2(readings[reading].Value, readings[reading].Angle);
	}
	accumulator /= readings.size();
	CDegrees angle = ToDegrees(accumulator.Angle());

	// If the angle is small enough and the closest obstacle is far enough
	if(angle >= -collisionAvoidanceParams.maxAngleBetweenHeadingAndObstacle && angle <= collisionAvoidanceParams.maxAngleBetweenHeadingAndObstacle
	&& accumulator.Length() < collisionAvoidanceParams.maxObstacleProximity) {
		// Go straight (left and right wheel turn with the same velocity)
		differentialSteeringActuator->SetLinearVelocity(velocity, velocity);
	}
	// Otherwise, turn a little, depending on the sign of the angle (range in radians is [-PI:PI])
	else {
		// Sensors with positive angles are located on the left side of the robot, sensors with negative angles are located on the right side of the robot
		if(angle.GetValue() > 0.0f) {
			// Turn right (only left wheel turns)
			differentialSteeringActuator->SetLinearVelocity(velocity, 0.0f);
		} else {
			// Turn left (only right wheel turns)
			differentialSteeringActuator->SetLinearVelocity(0.0f, velocity);
		}
	}

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
	// 		color.Set("red");
	// 		ledsActuator->SetAllColors(color);
	// 		fireDetected = true;
	// 		RLOG << "Fire detected: " << accumulator.Length() << std::endl;
	// 	}
	// } else {
	// 	differentialSteeringActuator->SetLinearVelocity(0.0f, 0.0f);
	// }
}

void FootBotBaseController::Reset() {
	// Reset all the LEDs in the ring to their initial state
	ledsActuator->SetAllColors(color);
}

// Macro that binds this class to an XML tag
REGISTER_CONTROLLER(FootBotBaseController, "footbot_base")