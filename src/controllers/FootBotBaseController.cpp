#include "FootBotBaseController.h"

FootBotBaseController::FootBotBaseController() :
	// Initialize attributes and set default values
	ledsColor("black"),
	color(0, 0, 0, 255),
	turnMode(TurnMode::NONE),
	behaviorState(BehaviorState::ROAMING) {
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
	GetNodeAttributeOrDefault(configurationNode, "leds_color", ledsColor, ledsColor);
	try {
		collisionAvoidanceParams.setParams(GetNode(configurationNode, "collision_avoidance"));
	} catch(CARGoSException &ex) {
	}
	try {
		movementParams.setParams(GetNode(configurationNode, "movement"));
	} catch(CARGoSException &ex) {
	}

	// Lit up all the LEDs in the ring with the same color and intensity
	color.Set(ledsColor);
	ledsActuator->SetAllColors(color);

	// Enable the colored blob omnidirectional camera sensor
	// coloredBlobOmnidirectionalCameraSensor->Enable();
}

void FootBotBaseController::ControlStep() {
	switch(behaviorState) {
		case BehaviorState::ROAMING: {
			roam();
			break;
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

	// Reset the turn mode to its initial state
	turnMode = TurnMode::NONE;

	// Reset the behavior state to its initial state
	behaviorState = BehaviorState::ROAMING;
}

void FootBotBaseController::roam() {
	// Get the vector that points directly away from a potential obstacle to perform collision avoidance
	CVector2 heading = getCollisionAvoidanceVector();

	// Set the velocities of both the left and the right wheels according to the maximum velocity and to where the robot should go
	setWheelVelocitiesFromVector(movementParams.maxVelocity * heading);	
}

CVector2 FootBotBaseController::getVectorToLight() {
	// Get readings from the light sensor
	const CCI_FootBotLightSensor::TReadings &readings = footBotLightSensor->GetReadings();

	// Get a new vector that points directly to the closest light using vector addition
	CVector2 vectorToClosestLight;
	for(size_t reading = 0, size = readings.size(); reading < size; reading++) {
		vectorToClosestLight += CVector2(readings[reading].Value, readings[reading].Angle);
	}

	// Return the zero vector if no light was perceived
	if(vectorToClosestLight.Length() == 0.0f) {
		return CVector2::ZERO;
	}
	// Otherwise return a unit vector to the light using vector normalization
	else {
		return vectorToClosestLight.Normalize();
	}
}

CVector2 FootBotBaseController::getCollisionAvoidanceVector() {
	// Get readings from the proximity sensor
	const CCI_FootBotProximitySensor::TReadings &readings = footBotProximitySensor->GetReadings();
	
	// Get a new vector that points directly to the closest obstacle using vector addition
	CVector2 vectorToClosestObstacle;
	for(size_t reading = 0, size = readings.size(); reading < size; reading++) {
		vectorToClosestObstacle += CVector2(readings[reading].Value, readings[reading].Angle);
	}

	// Ignore the obstacle and go straight if the angle to it is small enough and if it is far enough away
	// The sensors return a value between 0 (nothing within range) and 1 (obstacle touching sensor), which is why we need to use < instead of > when checking for the proximity of the obstacle
	CDegrees angle = ToDegrees(vectorToClosestObstacle.Angle());
	if(angle >= -collisionAvoidanceParams.maxAngleBetweenHeadingAndObstacle && angle <= collisionAvoidanceParams.maxAngleBetweenHeadingAndObstacle
	&& vectorToClosestObstacle.Length() < collisionAvoidanceParams.maxObstacleProximity) {
		return CVector2::X;
	}
	// Otherwise return a unit vector that points directly away from the closest obstacle using vector normalization and vector negation
	else {
		return -vectorToClosestObstacle.Normalize();
	}
}

void FootBotBaseController::setWheelVelocitiesFromVector(const CVector2 &heading) {
	// Get the angle of the heading as a value in the range [-180:180]
	CDegrees angle = ToDegrees(heading.Angle().SignedNormalize());

	// Limit the velocity to the maximum velocity
	Real velocity = heading.Length();
	if(velocity > movementParams.maxVelocity) {
		velocity = movementParams.maxVelocity;
	}

	// Determine which turn mode to use according to where the robot should go
	if(Abs(angle) >= movementParams.minHeadingAngleForHardTurn) {
		turnMode = TurnMode::HARD;
	} else if(Abs(angle) <= movementParams.maxHeadingAngleForNoTurn) {
		turnMode = TurnMode::NONE;
	} else {
		turnMode = TurnMode::SOFT;
	}

	// Set the wheel velocities according to the turn mode
	Real v1, v2;
	switch(turnMode) {
		// Wheels turn in the same direction with the same velocities (go straight)
		case TurnMode::NONE: {
			v1 = velocity;
			v2 = velocity;
			break;
		}
		// Wheels turn in the same direction with different velocities
		case TurnMode::SOFT: {
			Real factor = (movementParams.minHeadingAngleForHardTurn - Abs(angle)) / movementParams.minHeadingAngleForHardTurn;
			v1 = velocity - velocity * (1.0 - factor);
			v2 = velocity + velocity * (1.0 - factor);
			break;
		}
		// Wheels turn in opposite directions with the same velocities (turn on the spot)
		case TurnMode::HARD: {
			v1 = -movementParams.maxVelocity;
			v2 = movementParams.maxVelocity;
			break;
		}
	}

	// Apply the calculated velocities to the appropriate wheels depending on the sign of the angle
	if(angle.GetValue() > 0.0f) {
		// Turn left
		differentialSteeringActuator->SetLinearVelocity(v1, v2);
	} else {
		// Turn right
		differentialSteeringActuator->SetLinearVelocity(v2, v1);
	}
}

// Macro that binds this class to an XML tag
REGISTER_CONTROLLER(FootBotBaseController, "footbot_base")