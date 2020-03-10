CCI_Controller: https://www.argos-sim.info/api/a02036.php
CCI_DifferentialSteeringActuator: https://www.argos-sim.info/api/a02816.php
CCI_LEDsActuator: https://www.argos-sim.info/api/a02840.php
CCI_FootBotProximitySensor: https://www.argos-sim.info/api/a02656.php
    The sensors are evenly spaced on a ring around the base of the robot. Therefore, they do not turn with the turret.
CCI_FootBotGripperActuator: https://www.argos-sim.info/api/a02636.php
     It allows to set the gripper aperture in the range [-pi/2:pi/2]. The gripper can be locked in two directions: positive and negative. In the negative direction the 2 side pins of the gripper move upwards and the middle pin downwards.

footbot_flocking
footbot_foraging
footbot_synchronization
footbot_manualcontrol
footbot_nn

# Subklassen
- Temperatuursensors: vuur detecteren
- Grippers: objecten vastnemen

# Actuators
- Distance scanner: set angle and speed of rotating scanner. Higher range than proximity sensor.
- Radios: send messages to nearby radios.
- Range and bearing: situated wireless communication whereby the receiver also knows the location of the sender.

# Sensors
- Footbot distance scanner: read data of the scanner.
- Footbot base ground sensor: useful for detecting holes.
- Footbot motor ground sensor: useful for detecting changes in color on the ground.
- Footbot light sensor: detect lights.
- Differential steering: detect current position and orientation.
- Positioning: detect current position and orientation.
- Radios: receive message from nearby radios.
- Range and bearing: situated wireless communication whereby the receiver also knows the location of the sender.
- Light sensor: detect lights;
- Cameras: detect different objects.
- Colored blob omnidirectional camera: detect led of other robots.
- Colored blob perspective camera: detect led of other robots.
- Ground: 

# TODO
- Movable gates enkel movable door grippers (niet pushen dus, want anders zouden de andere bots dit ook kunnen bewegen, of niet?)
- Custom ending with loop function (all robots or large enough percentage are safe), or use predetermined time length?
- Velocity based control with differential_steering actuator, set max force and max torque in <dynamics2d> of <foot-bot> of <arena>.
- Andere example controllers en loop functions bekijken
- Heatmap + ground sensors (bottom sensors with gradient)
- Sensors need noise?
- Goede commentaar, attributen en variabelen in footbot_base
- Goede ids in configuration file
- Live graph view of emergent behaviour (linux system monitor)
- Based on what data does each individual robot decide?

# TODO 2
- Communicate with LEDs or radios?
- Do the gripping bots know the location of the gates or is this discovered by the swarm?
- Represent fire with light source, or with a changing floor texture depending on the temperature (sensed by the bots)?
- Distribute fire using random seed?
- The fire should spread?
- Once the bots have exited the gate, should they go to a predetermined location or just as far away from the fire as possible? As fare away as possible.
- Draw A and B choice textures/labels
- Arena size should pack 500 and use 100.
- Verwijder eventueel overbodige attributen in .argos

# Useful
- Communication by transmitting and detecting LEDs: synchronization.argos
- Custom trajectory drawing, loop and user functions: trajectory.argos
- Custom labels drawing with user function: id.argos
- Bottom sensors, floor textures, complete experiment, loop functions with params, user functions: foraging.argos