# TODO
- Finish gripper TODOs and optionally add the actual ability to open the gates
- Add a new movement mode: turn in a random direction every x timesteps to break up the grouping and mix the system better
- Determine the exit probability: how many times you exit with correct solution
- Test with 6 tiles per meter to position a fire exactly on the divider line
- Test with changing values of the gripper parameters
- Test with a runtime of 10 minutes
- Test with more than 1 fire source










# General
- Grippers: remove the gates and leave the nest (go as far away as possible)
- Sensors: locate the correct exit and leave the nest (go as far away as possible)

# Grippers
- Movable gates enkel movable door grippers, nu kunnen de andere bots de gates ook pushen (force/torque/friction van sensors verlagen, of mass van objects verhogen en enkel de gripper genoeg force/torque geven) (wat met de proximity sensors van de grippers, diffusion uitzetten, of logica met als de afstand tot het licht boven de gate gelijk is aan de max proximitysensor rijkwijdte, dan niet uitwijken, op voorwaarde dat die gate werd beslist in de swarm)
- Gates vervangen door gound blobs die alleen door de grippers opgepakt kunnen worden?
- Solid gates disappear when gripped, because the manouvering of the bots doesn't have much to do with the thesis novelty
- The cylinders can be fitted with LEDs

# Ending
- time limit or large enough percentage has left nest

# Dynamic
- dynamic_interval_ticks
- dynamic_temperature_increase
- dynamic_spread_direction

# Analysis
- Iterations: 30+
- See tweakable params below










# Data to communicate
- Temperature of tile
- Which exit to use
- The distance to that exit

# Individual decision mechanism
- Start when the robot moves from a white tile to a grayer tile
- Compute the distance to each exit
- Take the exit that is the furthest away from the fire
- Determine whether to update its opinion with a quality comparison

# Changing decision mechanism
- Reason: bots should be able to influence the opinion of other bots + bots with the highest temperature are not always reliable due to sensor noise
- Exchange data with neighbors
- Use a decision strategy to know when to replace your own data with the neighboring data and update your decision about the exit to use

# Individual reaction mechanism
- The grippers will hear the opinions being exchanged
- Apply a configurable quorum/threshold and time limit to know when to start acting

# Voting and decision strategies
- Plurality rule
- Majority rule
- Random rule

# Tweakable parameters than can have an influence on the result (! = important)
- ! amount of bots (and amount of each type)
- ! fire mode (and mode parameters)
- ! decision strategy mode
- ! reaction strategy parameters
- max_velocity (important in the dynamic scenario due to how fast the fire spreads)
- rab_range
- tiles_per_meter
- max_temperature
- sensor noise
- sensor packet drop
- arena shape and size










# Fire edge detection method
- Start building edge, but abandon when not enough robots participate (use probabilities)
- Grippers also move to detect the edges being formed

# Fire spreading method
- Compute the vector to each neighbor to compute the fire spreading vector (i.e. the direction to where the fire gets hotter)
- Compute the vector to each exit and compare them to the fire vector
- Choose the exit that coincides the least with the fire vector (i.e. if the fire is spreading towards the blue exit then pick the red exit and vice versa)
- See the flocking example (vector of motion => gradient vector of fire)
- Using the neighboring data (e.g. 0.1, 0.2, 0.1) you can get direction of the fire