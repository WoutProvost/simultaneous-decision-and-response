# Done
- Bugfix: random range right-open interval
- Bugfix: select max. value in map
- Bugfix: fix totalVots increment when adding robot's own opinion
- Bugfix: fix UInt8 overflow
- Bugfix: transmit distance in 2 bytes (integral and fractional parts)
- Bugfix: fix quality assignment after selecting executing voting model
- Added 2 optional extra choices for a total of 4
- Added support for random walk with configurable random_turn_ticks (defaults to no random walk)
- Added new decision strategy: best average quality
- All experiments use 6 tiles per meter
- Logic flowcharts

# TODO
- Determine the exit probability: how many times you exit with correct solution (definitely test with edge cases)
- Test with changing values of the gripper parameters
- Test with a runtime of 10 minutes
- Test with more than 1 fire source
- Algorithm doesn't work for multiple sources: position1="-7,-1.2" position2="0,1.2". Due to the left fire being further away in general from any exit, it will overpower the other fire that's actually more important. Need a way of assigning more quality to the central fire, or decrease the quality of the left fire in some way ...










# General
- Grippers: remove the gates and leave the nest (go as far away as possible)
- Sensors: locate the correct exit and leave the nest (go as far away as possible)

# Sensors
- While exiting the nest, the colored blob camera sensor should not be disabled by the subclass

# Ending
- time limit or large enough percentage has left nest

# Dynamic
- dynamic_interval_ticks
- dynamic_temperature_increase
- dynamic_spread_direction

# Tweakable parameters than can have an influence on the result (! = important)
- ! amount of bots (and amount of each type)
- ! fire mode (and mode parameters)
- ! decision strategy mode
- ! reaction strategy parameters
- ! random_turn_ticks
- max_velocity (important in the dynamic scenario due to how fast the fire spreads)
- rab_range
- tiles_per_meter
- max_temperature
- sensor noise
- sensor packet drop
- nest shape, size and obstacles