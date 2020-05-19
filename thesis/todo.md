# Done
- Each experiment uses a fixed amount of simulation timesteps which comes down to a length of 60 simulated minutes.
- Each experiment uses a single fire source with a fixed position along the Y axis and a fixed radius of 3.0 meters.
- Each experiment uses 100 temperature sensors and 100 gate grippers.
- Since the arena is symmetric, we need to test fewer cases.
- The fire positions are manually selected from easy to difficult to solve (see pictures for fire positions).
- Ran 650 experiments (see Experiments.ods for table).
- Discuss the other parameters to test (see reaction_ratios.png).

# TODO
- Try at least 3 values for each reaction strategy parameter (see which values are the most interesting)
- Try at least 3 population ratios, while keeping the total population size the same (see which values are the most interesting)
- When there's still some time left, try to change the random walk parameter
- When there's still some time left, try to change the random walk parameter, try to change the total population to 400

# Multiple sources
- position1="-7,-1.2" position2="0,1.2"
- The two distances from different sources to the same exit combined have a smaller difference than the two distances from different sources to the other exit combined
- Set of points A = fires, set of points B = exits. Determine which point in B is furthest/closest from the combination of points in A









# Install most recent ARGoS on node
wget -O - -q https://www.wall2.ilabt.iminds.be/enable-nat.sh | sudo bash
/groups/wall2-ilabt-iminds-be/cosy-swarm/exp/installArgos.sh
==> Upload 16.04 deb file
sudo dpkg -i argos3_simulator-3.0.0-x86_64-beta56.deb

# Custom CMakeLists.txt
```
cmake_minimum_required(VERSION 3.5)
project(simultaneous-decision-and-response LANGUAGES CXX)

# Set C++ standard to C++11
set(CMAKE_CXX_STANDARD 11)

# Find the PkgConfig package, for the pkg_check_modules method
find_package(PkgConfig)

# Find the ARGoS package and set some CMake ARGOS_* variables
pkg_check_modules(ARGOS REQUIRED argos3_simulator)

# Add a directory to be checked for .cmake files before using the default directories, for the find_package and include methods
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${ARGOS_PREFIX}/share/argos3/cmake)

# Find the Lua package, which is used in ci_sensor.h
find_package(Lua53 REQUIRED)

# Add these directories to those the compiler uses to search for include files
include_directories(${LUA_INCLUDE_DIR})

# Descend into these subdirectories
add_subdirectory(src/controllers)
add_subdirectory(src/loop_functions)
```

# Build project on node
mkdir simultaneous-decision-and-response
==> Upload experiments
==> Upload src
==> Upload CMakeLists.txt
mkdir build
cd build
cmake ..
make
mkdir ../logs
cd ../experiments