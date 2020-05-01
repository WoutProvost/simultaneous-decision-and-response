# Add these libraries to be built
add_library(footbot SHARED FootBotController.h FootBotController.cpp)
add_library(footbot_temperature_sensing MODULE FootBotTemperatureSensingController.h FootBotTemperatureSensingController.cpp)
add_library(footbot_gate_gripping MODULE FootBotGateGrippingController.h FootBotGateGrippingController.cpp)
add_library(movement SHARED params/MovementParams.h params/MovementParams.cpp)
add_library(collision_avoidance SHARED params/CollisionAvoidanceParams.h params/CollisionAvoidanceParams.cpp)
add_library(decision_strategy SHARED params/DecisionStrategyParams.h params/DecisionStrategyParams.cpp)
add_library(reaction_strategy SHARED params/ReactionStrategyParams.h params/ReactionStrategyParams.cpp)

# Define the dependencies of these libraries
target_link_libraries(footbot
	movement
	collision_avoidance)
target_link_libraries(footbot_temperature_sensing
	footbot
	decision_strategy
	fire_evacuation_loop_functions)
target_link_libraries(footbot_gate_gripping
	footbot
	reaction_strategy)