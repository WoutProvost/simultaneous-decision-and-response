#include "FootBotController.h"
#include "enums/RABIndex.h"

FootBotController::FootBotController() :
	// Initialize attributes and set default values
	ledsColor("black"),
	color(CColor::BLACK),
	turnMode(TurnMode::NONE),
	behaviorState(BehaviorState::ROAMING),
	coloredBlobOmnidirectionalCameraSensorEnabled(false) {
}

FootBotController::FootBotController(string ledsColor) :
	// Call other constructor
	FootBotController() {

	// Initialize attributes and set default values
	this->ledsColor = ledsColor;
}

void FootBotController::Init(TConfigurationNode &configurationNode) {
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

	// Add this LED color to the colored blobs that should be ignored when reading from the colored blob omnidirectional camera sensor
	ignoredColoredBlobs[color] = true;
}

void FootBotController::ControlStep() {
	// Execute correct behavior
	switch(behaviorState) {
		case BehaviorState::IDLE: {
			break;
		}
		case BehaviorState::ROAMING: {
			roam();
			break;
		}
	}
}

void FootBotController::Reset() {
	// Reset all the LEDs in the ring to their initial state
	ledsActuator->SetAllColors(color);

	// Clear all data that is still in the buffer
	rangeAndBearingActuator->ClearData();

	// Reset the turn mode to its initial state
	turnMode = TurnMode::NONE;

	// Reset the behavior state to its initial state
	behaviorState = BehaviorState::ROAMING;

	// Disable the colored blob omnidirectional camera sensor
	coloredBlobOmnidirectionalCameraSensor->Disable();
	coloredBlobOmnidirectionalCameraSensorEnabled = false;
}

void FootBotController::roam() {
	// Get the vector that points directly away from a potential obstacle to perform collision avoidance
	CVector2 heading = getCollisionAvoidanceVector();

	// Set the velocities of both the left and the right wheels according to the maximum velocity and to where the robot should go
	setWheelVelocitiesFromVector(movementParams.maxVelocity * heading);
}

CVector2 FootBotController::getVectorToLight() {
	// Get readings from the light sensor
	const CCI_FootBotLightSensor::TReadings &readings = footBotLightSensor->GetReadings();

	// Get a new vector that points directly to the closest light using vector addition
	CVector2 vectorToClosestLight;
	for(size_t reading = 0, size = readings.size(); reading < size; reading++) {
		vectorToClosestLight += CVector2(readings[reading].Value, readings[reading].Angle);
	}

	// Return the zero vector if no light was perceived
	if(vectorToClosestLight.Length() == 0.0) {
		return CVector2::ZERO;
	}
	// Otherwise return a unit vector to the light using vector normalization
	else {
		return vectorToClosestLight.Normalize();
	}
}

CVector2 FootBotController::getCollisionAvoidanceVector() {
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

void FootBotController::setWheelVelocitiesFromVector(const CVector2 &heading) {
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
	if(angle.GetValue() > 0.0) {
		// Turn left
		differentialSteeringActuator->SetLinearVelocity(v1, v2);
	} else {
		// Turn right
		differentialSteeringActuator->SetLinearVelocity(v2, v1);
	}
}

// Static variables and constants initialization
map<uint32_t,bool> FootBotController::ignoredColoredBlobs = map<uint32_t,bool>();

// Macro that binds this class to an XML tag
REGISTER_CONTROLLER(FootBotController, "footbot")