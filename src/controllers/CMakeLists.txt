# Add these libraries to be built
add_library(footbot SHARED FootBotController.h FootBotController.cpp)
add_library(temperature_sensing_footbot MODULE TemperatureSensingFootBotController.h TemperatureSensingFootBotController.cpp)
add_library(gate_gripping_footbot MODULE GateGrippingFootBotController.h GateGrippingFootBotController.cpp)
add_library(appearance SHARED params/AppearanceParams.h params/AppearanceParams.cpp)
add_library(movement SHARED params/MovementParams.h params/MovementParams.cpp)
add_library(collision_avoidance SHARED params/CollisionAvoidanceParams.h params/CollisionAvoidanceParams.cpp)
add_library(decision_strategy SHARED params/DecisionStrategyParams.h params/DecisionStrategyParams.cpp)
add_library(reaction_strategy SHARED params/ReactionStrategyParams.h params/ReactionStrategyParams.cpp)

# Define the dependencies of these libraries
target_link_libraries(footbot
	appearance
	movement
	collision_avoidance)
target_link_libraries(temperature_sensing_footbot
	footbot
	decision_strategy
	fire_evacuation_loop_functions)
target_link_libraries(gate_gripping_footbot
	footbot
	reaction_strategy)