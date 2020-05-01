# Done
- Random voting model that just takes the opinion of a random neighbour (quality assumption still used)

# TODO
- Read additional article for the weighted voter model
- Use two parameters for the gripper reaction mechanism: percentage and timesteps
- The gripper starts acting when a percentage x holds for y amount of time










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
- Exchange data with neighbours
- Apply a threshold (voting strategy) to know when to replace your own data with the neighbouring data and update your decision about the exit to use

# Individual reaction mechanism
- The grippers will hear the opinions being exchanged
- Apply a configurable quorum/threshold and time limit to know when to start acting

# Voting and decision strategies
- Plurality rule
- Majority rule
- Random rule
- Weighted voter model

# Tweakable parameters than can have an influence on the result (! = important)
- ! amount of bots (and amount of each type)
- ! fire mode (and mode parameters)
- ! voting strategy mode (and mode parameters)
- ! gripper percentage and time
- max_velocity (important in the dynamic scenario due to how fast the fire spreads)
- rab_range
- tiles_per_meter
- max_temperature
- sensor noise
- sensor packet drop
- arena shape










# Fire edge detection method
- Start building edge, but abandon when not enough robots participate (use probabilities)
- Grippers also move to detect the edges being formed

# Fire spreading method
- Compute the vector to each neighbour to compute the fire spreading vector (i.e. the direction to where the fire gets hotter)
- Compute the vector to each exit and compare them to the fire vector
- Choose the exit that coincides the least with the fire vector (i.e. if the fire is spreading towards the blue exit then pick the red exit and vice versa)
- See the flocking example (vector of motion => gradient vector of fire)
- Using the neighbouring data (e.g. 0.1, 0.2, 0.1) you can get direction of the fire