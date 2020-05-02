# Add these libraries to be built
add_library(fire_evacuation_user_functions MODULE FireEvacuationUserFunctions.h FireEvacuationUserFunctions.cpp)
add_library(divider SHARED params/DividerParams.h params/DividerParams.cpp)

# Define the dependencies of these libraries
target_link_libraries(fire_evacuation_user_functions
	divider)