# Done
- Each experiment uses a fixed length of 60 minutes, unless it was clear that the experiment needed more time

# TODO
- Determine the exit probability: how many times you exit with correct solution (definitely test with edge cases)
- Test with changing values of the gripper parameters
- Test with a runtime of 10 minutes
- Test with more than 1 fire source
- Test with manually selecting fire source locations, from easy to difficult for the swarm to solve
- Algorithm doesn't work for multiple sources: position1="-7,-1.2" position2="0,1.2"

# Tweakable parameters than can have an influence on the result
- amount of bots (and amount of each type)
- fire mode (and mode parameters, circle radius, ...)
- decision strategy mode
- reaction strategy parameters
- random_turn_ticks (less priority than others above)










# General
- Grippers: remove the gates and leave the nest (go as far away as possible)
- Sensors: locate the correct exit and leave the nest (go as far away as possible)

# Sensors
- While exiting the nest, the colored blob camera sensor should not be disabled by the subclass

# Dynamic
- dynamic_interval_ticks
- dynamic_temperature_increase
- dynamic_spread_direction