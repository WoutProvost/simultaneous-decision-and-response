cmake_minimum_required(VERSION 3.10)
project(simultaneous-decision-and-response
	VERSION 1.0.0
	DESCRIPTION "Simultaneous decision and response in a collective system using swarm robotics and collective decision making in a fire evacuation scenario"
	LANGUAGES CXX)

# Find the PkgConfig package, for the pkg_check_modules method
find_package(PkgConfig)

# Find the ARGoS package and set some CMake ARGOS_* variables
pkg_check_modules(ARGOS REQUIRED argos3_simulator)

# Add a directory to be checked for .cmake files before using the default directories, for the find_package and include methods
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${ARGOS_PREFIX}/share/argos3/cmake)

# Find the Lua package, which is used in ci_sensor.h
find_package(Lua53 REQUIRED)

# Check if all the necessary libraries have been installed to use Qt and OpenGL
include(ARGoSCheckQTOpenGL)

# Add these directories to those the compiler uses to search for include files
include_directories(${LUA_INCLUDE_DIR})

# Descend into these subdirectories
add_subdirectory(src/controllers)
add_subdirectory(src/loop_functions)
add_subdirectory(src/user_functions)
add_subdirectory(src/plot)
add_subdirectory(src/seed)