#include "footbot_base.h"
#include <argos3/core/utility/configuration/argos_configuration.h>
#include <argos3/core/utility/math/vector2.h>

CFootBotBase::CFootBotBase() :
	m_pcDifferentialSteeringActuator(NULL),
	m_pcProximitySensor(NULL),
	m_fVelocity(2.5f),
	m_cMaxAngleBetweenHeadingAndObstacle(10.0f),
	m_fMaxObstacleProximity(0.5f),
	m_cGoStraightAngleRange(-ToRadians(m_cMaxAngleBetweenHeadingAndObstacle), ToRadians(m_cMaxAngleBetweenHeadingAndObstacle)) {}

void CFootBotBase::Init(TConfigurationNode& t_node) {
	// Get actuators and sensors
	m_pcDifferentialSteeringActuator = GetActuator<CCI_DifferentialSteeringActuator>("differential_steering");
	m_pcProximitySensor = GetSensor<CCI_FootBotProximitySensor>("footbot_proximity");

	// Parse the configuration file
	GetNodeAttributeOrDefault(t_node, "velocity", m_fVelocity, m_fVelocity);
	GetNodeAttributeOrDefault(t_node, "max_angle_between_heading_and_obstacle", m_cMaxAngleBetweenHeadingAndObstacle, m_cMaxAngleBetweenHeadingAndObstacle);
	GetNodeAttributeOrDefault(t_node, "max_obstacle_proximity", m_fMaxObstacleProximity, m_fMaxObstacleProximity);
	m_cGoStraightAngleRange.Set(-ToRadians(m_cMaxAngleBetweenHeadingAndObstacle), ToRadians(m_cMaxAngleBetweenHeadingAndObstacle));
}

void CFootBotBase::ControlStep() {
	// Get readings from the proximity sensor
	const CCI_FootBotProximitySensor::TReadings &tProxReads = m_pcProximitySensor->GetReadings();

	// Sum these readings together in a vector2
	CVector2 cAccumulator;
	for(size_t i = 0, size = tProxReads.size(); i < size; i++) {
		cAccumulator += CVector2(tProxReads[i].Value, tProxReads[i].Angle);
	}
	cAccumulator /= tProxReads.size();
	CRadians cAngle = cAccumulator.Angle();

	// If the angle between the heading and the obstacle is small enough and the closest obstacle is far enough
	if(m_cGoStraightAngleRange.WithinMinBoundIncludedMaxBoundIncluded(cAngle) && cAccumulator.Length() < m_fMaxObstacleProximity) {
		// Go straight (left and right wheel turn with the same velocity)
		m_pcDifferentialSteeringActuator->SetLinearVelocity(m_fVelocity, m_fVelocity);
	}
	// Otherwise, turn a little, depending on the sign of the angle
	else {
		if(cAngle.GetValue() > 0.0f) {
			// Turn right (only left wheel turns)
			m_pcDifferentialSteeringActuator->SetLinearVelocity(m_fVelocity, 0.0f);
		} else {
			// Turn left (only right wheel turns)
			m_pcDifferentialSteeringActuator->SetLinearVelocity(0.0f, m_fVelocity);
		}
	}
}

// Macro that binds this class to an XML tag
REGISTER_CONTROLLER(CFootBotBase, "footbot_base_controller")