cmake_minimum_required(VERSION 3.10)
project(fire_evacuation
	VERSION 1.0.0
	DESCRIPTION "Swarm robotics and collective decision making in a fire evacution scenario"
	#HOMEPAGE_URL "https://github.com/WoutProvost/swarm-robotics-thesis"
	LANGUAGES CXX)

# Find the PkgConfig package, for the pkg_check_modules method
find_package(PkgConfig)

# Find the ARGoS package
pkg_check_modules(ARGOS REQUIRED argos3_simulator)

# Set the ARGoS prefix
set(ARGOS_PREFIX ${ARGOS_PREFIX} CACHE INTERNAL "")

# Add a path to the list of directories for packages that should be checked first before the default packages, for the find_package and include methods
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${ARGOS_PREFIX}/share/argos3/cmake)

# Find the Lua package
find_package(Lua53 REQUIRED)

# Check whether all the necessary libraries have been installed to compile the code that depends on Qt and OpenGL
include(ARGoSCheckQTOpenGL)

# Add these directories to those the compiler uses to search for include files
include_directories(${CMAKE_SOURCE_DIR} ${ARGOS_INCLUDE_DIRS} ${LUA_INCLUDE_DIR})
include_directories(controllers)
include_directories(loop_functions)
include_directories(user_functions)

# Add these directories to those the linker uses to search for libraries
link_directories(${ARGOS_LIBRARY_DIRS})

# Descend into these subdirectories
add_subdirectory(controllers)
add_subdirectory(loop_functions)
add_subdirectory(user_functions)