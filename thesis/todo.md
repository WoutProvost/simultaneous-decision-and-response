CCI_Controller: https://www.argos-sim.info/api/a02036.php
CCI_DifferentialSteeringActuator: https://www.argos-sim.info/api/a02816.php
CCI_FootBotProximitySensor: https://www.argos-sim.info/api/a02656.php
    The sensors are evenly spaced on a ring around the base of the robot. Therefore, they do not turn with the turret.

https://github.com/WoutProvost/swarm-robotics-thesis/blob/master/documentation/documentation.md
https://github.com/ilpincy/argos3/tree/master/src/plugins/robots/foot-bot/control_interface
https://www.argos-sim.info/api/annotated.php
footbot_flocking
footbot_foraging
footbot_gripping
footbot_synchronization
footbot_manualcontrol
footbot_nn

# TODO
- Kijk alles van CMake na, en probeer het te verstaan...
- Goede commentaar in footbot_base e.a.
- Goede attribuut en variabele namen in footbot_base e.a.
- Verwijder eventueel overbodige attributen in .argos
- Bekijk afbeelding nog eens.
- Documentation: footbot_proximity kan ook rays tonen, en mss ook noise.

- footbot turret color, obv welk type, zet in configuration file
- Custom ending with loop function (all robots safe), or use predetermined time length?
- Velocity based control with differential_steering actuator, set max force and max torque in <dynamics2d> of <foot-bot> of <arena>.
- Andere example controllers en loop functions bekijken
- Movable gates enkel movable door grippers (niet pushen dus, want anders zouden de andere bots dit ook kunnen bewegen, of niet?)
- It is possible to add any number of colored LEDs to the box. In this way, the box is visible with a robot camera. The position and color of the
LEDs is specified with the following syntax: argos3 -q box
- Heatmap + ground sensors (bottom sensors with gradient)
- Sensors need noise?

# TODO 2
- Communicate with LEDs?
- Do the gripping bots know the location of the gates or is this discovered by the swarm?
- Represent fire with light source, or with a changing floor texture depending on the temperature (sensed by the bots)?
- Distribute fire using random seed?
- The fire should spread?
- Once the bots have exited the gate, should they go to a predetermined location or just as far away from the fire as possible? As fare away as possible.
- Draw A and B choice textures/labels
- Arena size should pack 500 and use 100.

# Useful
- Communication by transmitting and detecting LEDs: synchronization.argos
- Gripper bots and movable objects using a simple time-based logic: gripping.argos
- Custom trajectory drawing, loop and user functions: trajectory.argos
- Custom labels drawing with user function: id.argos
- Bottom sensors, floor textures, complete experiment, loop functions with params, user functions: foraging.argos