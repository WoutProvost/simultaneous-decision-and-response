# Add these libraries to be built
# SHARED = linked dynamically into other targets and loaded at runtime
# MODULE = not linked into other targets and loaded dynamically at runtime
add_library(fire_evacuation_loop_functions MODULE FireEvacuationLoopFunctions.h FireEvacuationLoopFunctions.cpp)
add_library(heatmap SHARED params/HeatMapParams.h params/HeatMapParams.cpp)
add_library(fire SHARED params/FireParams.h params/FireParams.cpp)

# Define which other libraries these libraries depend on
target_link_libraries(fire_evacuation_loop_functions
	argos3core_simulator
	heatmap
	fire)