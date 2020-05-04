# Done
- Added reaction mechanism + params min_agreement_percentage and min_duration_ticks
- Added support for response data in logfile and plot app
- Added user functions with divider ray
- Added debug option to bots to show their preferred exit using their LEDs (slightly altered colors so that the bot won't be detected as an exit)
- Added random neighbour voting model (robot's own opinion not added to list of valid readings in this model)
- Always use quality comparisons, regardless of color of neighbours and for all voting models
- Fix integer division
- Fix crucial logfile color bug which caused the data to be mapped to the wrong exit

# TODO
- Read additional article for the weighted voter model

# IMPORTANT!!!!
- Algorithm works perfect when the fire is on a clear side of the arena.
- Problems occur when the fire is accross the center line between the 2 exits
- However, there's actually a great conclusion to this (see the arrows below).
1. Due to the used collision avoidance code, the bots tend to bunch up in groups.
   This group constantly reassures one exit for all the members in that group, since it has the numbers to overpower any new measurement by a member of that group.
   When a bot not part of that group collides with the group, it takes over the decision of the group, since the group has the numbers to overpower any other bot.
   Demonstration: seed 648, 200 sensors, 0 grippers, show preference color, after tick 1700.
2. Bots that haven't made any measurements of their own get convinced rather quickly by other bots that have made measurements.
   This has an almost exponential effect.
   Demonstration: seed 648, 200 sensors, 0 grippers, show preference color.
3. Bots on the opposite side of the bulk of the fire don't get many chances to make measurements of their own, since the bulk of the fire is on the opposite side.
   Due to the used collision avoidance code, crossing that center line to get to the bulk of the fire might be difficult.
=> The closer that the fire is to the center line, the more that the result depends on the initial positions and rotations of the bots and their movement.
=> No voting model actually has better results, but obviously takes way too long.
=> Random voting model actually has better results and is very fast.
   In a one-on-one situation there's only one neighbour, thus the probability of that neighbour being picked is 100%.
   Bots on the side of the bulk of the fire will be higher in numbers and thus their probability of being picked is also higher.
   Both effects lead to the correct result.
=> Due to the group forming, over time it actually starts looking like a real flock of birds.
   Demonstration: seed 648, 100 sensors, 100 grippers, no voting model, just let it run for a while.










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
- Use a decision strategy to know when to replace your own data with the neighbouring data and update your decision about the exit to use

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
- Compute the vector to each neighbour to compute the fire spreading vector (i.e. the direction to where the fire gets hotter)
- Compute the vector to each exit and compare them to the fire vector
- Choose the exit that coincides the least with the fire vector (i.e. if the fire is spreading towards the blue exit then pick the red exit and vice versa)
- See the flocking example (vector of motion => gradient vector of fire)
- Using the neighbouring data (e.g. 0.1, 0.2, 0.1) you can get direction of the fire