# Add these libraries to be built
add_library(fire_evacuation_loop_functions SHARED FireEvacuationLoopFunctions.h FireEvacuationLoopFunctions.cpp)
add_library(nest SHARED params/NestParams.h params/NestParams.cpp)
add_library(heatmap SHARED params/HeatMapParams.h params/HeatMapParams.cpp)
add_library(fire SHARED params/FireParams.h params/FireParams.cpp)
add_library(log SHARED params/LogParams.h params/LogParams.cpp)

# Define the dependencies of these libraries
target_link_libraries(fire_evacuation_loop_functions
	nest
	heatmap
	fire
	log)