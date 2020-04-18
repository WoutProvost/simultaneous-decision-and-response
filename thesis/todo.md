# Done
- The robots don't continuously change their opinion anymore, but only change it when they've found a better one
- The robots don't communicate their last measured value anymore, but only communicate their best measurement (see above)
- The robots don't just communicate when they are measuring anymore (i.e. when they're not on a white tile), but once they've formulated an opinion, they communicate this continuously
- The robot's opinion is now based upon the distance weighted with the temperature, so that there is a quality associated with the measurement, which allows for easy quality comparisons, e.g. a fire that's not very hot but very close to one exit has less priority than a fire that's very hot and very close to that exit
- The robot's opinion can now be influenced by the opinion of its neighbors using various voting models
- The robot's current opinion is counted as a vote in the voting mechanism
- One assumption is made when changing a robot's opinion based on the neighbouring opinions, if the voting model results in an exit that is the same as the exit the robot is currently preferring, then it will only update its distance and temperature if the neighbouring measurement quality is better than its own measurement quality
- The grippers don't participate in the decision making, they only listen to the data traffic
- Additional fire sources

# TODO
- Weighted voter model
- Configurable threshold other than 50%
- Determine when to start the collective response using a quorum/threshold
- Response speed vs accuracy trade-off








# Data to communicate
- Temperature of tile
- Which exit to use
- The distance to that exit

# Individual decision mechanism
- Start when the robot moves from a white tile to a grayer tile
- Compute the distance to each exit
- Choose the exit that is the furthest away from the fire

# Changing decision mechanism
- Reason: bots should be able to influence the opinion of other bots + bots with the highest temperature are not always reliable due to sensor noise
- Exchange data with neighbours
- Apply a threshold (voting strategy) to know when to replace your own data with the neighbouring data and update your decision about the exit to use
- Take the average of what the neighbours exchange with you

# Individual reaction mechanism
- The grippers will hear the opinions being exchanged
- Apply a quorum/threshold to know when to start acting
- Avoid cases where grippers start taking decisions too early, but at the same time you don't want them to wait too long (speed vs accuracy trade-off)

# Voting and decision strategies
- Plurality rule
- Majority rule
- Weighted voter model
- Configurable threshold other than 50%










# Fire edge detection method
- Start building edge, but abandon when not enough robots participate (use probabilities)
- Grippers also move to detect the edges being formed

# Fire spreading method
- Compute the vector to each neighbour to compute the fire spreading vector (i.e. the direction to where the fire gets hotter)
- Compute the vector to each exit and compare them to the fire vector
- Choose the exit that coincides the least with the fire vector (i.e. if the fire is spreading towards the blue exit then pick the red exit and vice versa)
- See the flocking example (vector of motion => gradient vector of fire)
- Using the neighbouring data (e.g. 0.1, 0.2, 0.1) you can get direction of the fire










# TODO
- Gates: only removable by the gripper robots
- Gripper robots: remove the gates and exit the arena
- Sensor robots: search for an exit and exit the arena
- Dynamic fire circle: dynamic_interval_ticks, dynamic_temperature_increase
- Colored heatmap: could work when subclassing the motor ground sensor

# Grippers
- Movable gates enkel movable door grippers, nu kunnen de andere bots de gates ook pushen (force/torque/friction van sensors verlagen, of mass van objects verhogen en enkel de gripper genoeg force/torque geven) (wat met de proximity sensors van de grippers, diffusion uitzetten, of logica met als de afstand tot het licht boven de gate gelijk is aan de max proximitysensor rijkwijdte, dan niet uitwijken, op voorwaarde dat die gate werd beslist in de swarm)
- Gates vervangen door gound blobs die alleen door de grippers opgepakt kunnen worden?
- Solid gates disappear when gripped, because the manouvering of the bots doesn't have much to do with the thesis novelty
- The cylinders can be fitted with LEDs

# Plot
- Implement plot configuration params.

# Ending
- Custom ending with loop function: all robots or large enough percentage are safe
- Once the bots have exited the gate they should go as fare away as possible from the fire

# Analysis
- Amount of agents: [50;100] scaling environment
- Iterations: 30+
- Cohesion threshold: 80+%

# Tweakable parameters than can have an influence on the result
- max_velocity (important in the dynamic scenario due to how fast the fire spreads)
- rab_range
- tiles_per_meter
- max_temperature
- sensor noise
- sensor packet drop
- amount of bots (and amount of each type)
- fire mode (and mode parameters)
- voting strategy mode (and mode parameters)

# Documentation
- CDynamics2DFootBotModel: https://www.argos-sim.info/api/a00521_source.php
- CCI_Controller: https://www.argos-sim.info/api/a02036.php
- CCI_DifferentialSteeringActuator: https://www.argos-sim.info/api/a02816.php
- CCI_LEDsActuator: https://www.argos-sim.info/api/a02840.php
- CCI_RangeAndBearingActuator: https://www.argos-sim.info/api/a02896.php
- CCI_FootBotGripperActuator: https://www.argos-sim.info/api/a02636.php
- CCI_FootBotProximitySensor: https://www.argos-sim.info/api/a02656.php
- CCI_RangeAndBearingSensor: https://www.argos-sim.info/api/a02900.php
- CCI_ColoredBlobOmnidirectionalCameraSensor: https://www.argos-sim.info/api/a02792.php
- CCI_FootBotLightSensor: https://www.argos-sim.info/api/a02640.php
- CCI_FootBotMotorGroundSensor: https://www.argos-sim.info/api/a02648.php

# Performance notes
- For larger swarms, turning the light sensor of when you don't need it.
- For larger swarms, turning the camera sensor of when you don't need it.
- For less than 100 robots, thread management is not beneficial.
- For swarms larger than 50 robots and/or large arenas, multiple physics engines should be used.
- Use the same number of threads as there are physics engines and take into account the amount of CPU cores.