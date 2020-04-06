# Data to communicate
- Temperature of tile
- Which exit to use

# Individual decision mechanism
Start when the robot moves from a white tile to a grayer tile
## Distance method
- Compute the distance to each exit
- Choose the exit that is the furthest away from the fire
## Fire spreading method
- Compute the vector to each neighbour to compute the fire spreading vector (i.e. the direction to where the fire gets hotter)
- Compute the vector to each exit and compare them to the fire vector
- Choose the exit that coincides the least with the fire vector (i.e. if the fire is spreading towards the blue exit then pick the red exit and vice versa)
- See the flocking example (vector of motion => gradient vector of fire)

# Changing decision mechanism
Reason: bots with highest temperature are not always reliable
Exchange data with neighbours
Apply a threshold to know when to replace your own data with the neighbouring data and update your decision about the exit to use
## Average method
- Take the average of what the neighbours exchange with you
## Fire spreading method
- Using the neighbouring data (e.g. 0.1, 0.2, 0.1) you can get direction of the fire

# Individual reaction mechanism
- The grippers will hear the opinions being exchanged
- Apply a threshold to know when to start acting
- Avoid cases where grippers start taking decisions too early, but at the same time you don't want them to wait too long (speed vs accuracy trade off)

# Voting and decision strategies
- Majority rule, weighted voter model, quorum sensing, ... (see the articles)
- Implement at least 2 voting mechanisms to compare
- Determine which exit is closer to the center of mass of the swarm (only useful when the swarm is not uniformly divided)










# Majority rule opinion formation model:
- robots agree on a common decision by applying a local majority rule to small groups
- use a latency period after each robot takes a decision, during which the robot cannot be influenced by other robots
- if the duration of this period depends on the decision being taken (differential latency), then a global consensus is achieved on the decision associated with the lowest latency
- 1. robots enter an observation state, where they exchange their current preferred action, after each action execution
- 2. robots transmit their preference to neighboring robots for a time duration proportional to the perceived quality of the site associated to their current preference
- 3. robots have the tendency to reach a specific goal and the tendency to follow the average behavior of its neighbors, change weight of both components dynamically based on the local consensus to converge to a collective decision even in precense of informed agents with conflicting goals

# Consensus achievement:
- the best choice may change over time or may not be evident to the robots due to their limited sensing capabilities
- each robot is able to communicate its preferred choice
- 1. the robots simply follow the robot closest to a target, resulting in a decision based on the spatial distribution of the swarm
- 2. the robots vote, using a majority rule, to decide which target to follow
- when two robots get close, they exchange their measured distances
- each robot performs an average of its measured distance with the one received from the other robots
- the robots are able to agree on a choice and discard the other one even when the measured distances are noisy
- when a robot finds a new alternative, it evaluates its quality and sends recruiting messages to other robots to advertise it
- the frequency of these messages is proportional to the perceived quality of the alternative
- thanks to the different message frequencies associated with the different alternatives, over time all robots converge on the best alternative

# Design pattern for best-of-n decision problem:
- each option `i` is characterised by a quality `v_i`
- population `A` of `N` agents where each agent `a_g` is either committed to one of the available options `i` and belongs to the sub-population `A_i` of `N_i` agents and thus fraction `W_i = N_i/N`
- agents can obtain a noisy estimate `^v_i` of the quality associated to option `i`
- a decision is taken as soon as the entire population, or a large fraction `W_q` (quorum) is committed to a single option
- a probabilistic finite state machine (PFSM) to describe the behaviour of the individual agent that changes its commitment state in response to probabilistic events

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
- Custom ending with loop function (all robots or large enough percentage are safe), or use predetermined time length?
- Once the bots have exited the gate they should go as fare away as possible from the fire
- Perhaps only show the colorized heatmap right before the experiment ends
- Additional fire modes: each mode should have its own configuration node, so it's easier to have its own attributes (multiple fires, dynamic fire, ...)

# Analysis
- Amount of agents: [50;100] scaling environment
- Iterations: 30+
- Cohesion threshold: 80+%

# Tweakable parameters than can have an influence on the result
- max_velocity (important in the dynamic scenario due to how fast the fire spreads)
- rab_range
- rab_data_size
- tiles_per_meter
- max_temperature
- sensor noise
- sensor packet drop
- amount of bots (and amount of each type)

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