# Controllers
## Foot-bot
Wheeled modular robot with a rich set of sensors and actuators.
- rab_range attribute
- rab_data_size attribute
- battery element
- omnidirectional_camera_aperture attribute
- perspective_camera_front, perspective_camera_aperture, perspective_camera_focal_length, perspective_camera_range attributes

## E-puck
Two-wheeled robot equipped with proximity sensors, ground sensors, light sensors, a microphone, a frontal camera, and a ring of red LEDs.
- rab_range attribute
- rab_data_size attribute
- battery element

## Eye-bot
Quad-rotor robot with a rich set of sensors and actuators.
- rab_range attribute
- rab_data_size attribute
- battery element
- camera_aperture, camera_focal_length, camera_range attributes

## Spiri
Quad-rotor robot with a rich set of sensors and actuators.
- rab_range attribute
- rab_data_size attribute
- battery element

# Media
## Radio
This medium indexes the radio entities in the space and allows transmitting radios to find nearby receiving radios.

## Range and bearing
This medium is required to simulate communication across range-and-bearing-equipped robots.
By default, the RAB medium requires two robots to be in direct line-of-sight in order to be able to exchange messages. You can toggle this behavior on or off through the 'check_occlusions' attribute.
Allows robots to perform situated communication, i.e., a form of wireless communication whereby the receiver also knows the location of the sender with respect to its own frame of reference.

## LED
This medium is required to manage the LED entities, thus allowing the associated camera sensors to work properly.

## Directional LED
This medium is required to manage the directional LED entities, thus allowing the associated camera sensors to work properly.

## Tag
This medium is required to manage the tag/qrcodes entities, so that the associated camera sensors can find them.

# Actuators
## Footbot distance scanner
This actuator controls the foot-bot distance scanner.

## Footbot gripper
This actuator controls the foot-bot gripper.

## Footbot turret
This actuator controls the foot-bot turret.

## Differential steering
This actuator controls the two wheels a differential steering robot.
It is possible to specify noisy speed in order to match the characteristics of the real robot, using additional attributes.
The noise can be configured for each wheel differently.

## Gripper
This actuator controls a gripper.

## Radios
This radio actuator implementation allows an arbitary number of messages containing an arbitary number of bytes to be sent to nearby radios.
The 'medium' attribute sets the id of the radio medium.

## Range and bearing
This actuator allows robots to perform situated communication, i.e., a form of wireless communication whereby the receiver also knows the location of the sender with respect to its own frame of reference.
This actuator allows a robot to send messages.

## LEDs
This actuator controls a group of LEDs.
The 'medium' attribute sets the id of the LED medium.

## Directional LEDs
This actuator controls a group of directional LEDs.
The 'medium' attribute sets the id of the LED medium.

## Magnets
This actuator is used to modify the magnetic field of a magnet entity in the simulation.
A magnetic entity has a passive and an active field.

## Tags
This actuator controls the payloads of a group of tags. The ideais to represent an LCD screen that displays different tags.

## Joints
This actuator is used to control the joints inside a prototype entity.

# Sensors
## Footbot distance scanner (rot_z_only)
This sensor accesses the foot-bot distance scanner sensor.
With the show_rays option, you can see whether or not a target was partially occluded by another object in the simulation (cyan=unobstructed, purple=obstructed).

## Footbot turret encoder
This sensor accesses the foot-bot turret encoder.

## Footbot proximity
This sensor accesses the foot-bot proximity sensor.

## Footbot base ground (rot_z_only)
This sensor accesses the foot-bot base ground sensor.

## Footbot motor ground (rot_z_only)
This sensor accesses the foot-bot motor ground sensor.

## Footbot light (rot_z_only)
This sensor accesses a set of light sensors.
The sensors all return a value between 0 and 1, where 0 means nothing within range and 1 means the perceived light saturates the sensor.
With the show_rays option, you can see whether or not a target was partially occluded by another object in the simulation (cyan=unobstructed, purple=obstructed).
It is possible to add uniform noise to the sensor, thus matching the characteristics of a real robot better.

## Epuck proximity
This sensor accesses a set of proximity sensors.
The sensors all return a value between 0 and 1, where 0 means nothing within range and 1 means an external object is touching the sensor.
With the show_rays option, you can see whether or not a target was partially occluded by another object in the simulation (cyan=unobstructed, purple=obstructed).
It is possible to add uniform noise to the sensor, thus matching the characteristics of a real robot better.

## Differential steering
This sensor returns the current position and orientation of a robot.
This sensor can be used with any robot, since it accesses only the body component.
It is possible to add uniform noise to the sensor, thus matching the characteristics of a real robot better.

## Positioning
This sensor returns the current position and orientation of a robot.
This sensor can be used with any robot, since it accesses only the body component.
It is possible to add uniform noise to the blobs, thus matching the characteristics of a real robot better.

## Proximity
This sensor accesses a set of proximity sensors.
The sensors all return a value between 0 and 1, where 0 means nothing within range and 1 means an external object is touching the sensor.
With the show_rays option, you can see whether or not a target was partially occluded by another object in the simulation (cyan=unobstructed, purple=obstructed).
It is possible to add uniform noise to the blobs, thus matching the characteristics of a real robot better.

## Radios
This radio sensor implementation allows an arbitary number of messages containing an arbitary number of bytes to be received from nearby robots.
The 'medium' attribute sets the id of the radio medium.

## Range and bearing (medium)
This sensor allows robots to perform situated communication, i.e., a form of wireless communication whereby the receiver also knows the location of the sender with respect to its own frame of reference.
This sensor allows a robot to receive messages.
The 'medium' attribute sets the id of the rab medium.
With the show_rays option, you can see whether or not a target was partially occluded by another object in the simulation (cyan=unobstructed, purple=obstructed).
It is possible to add uniform noise to the blobs, thus matching the characteristics of a real robot better.
It is possible to specify the probability that a packet gets lost even though the robot should have received it (i.e., packet dropping).

## Light
This sensor accesses a set of light sensors.
The sensors all return a value between 0 and 1, where 0 means nothing within range and 1 means the perceived light saturates the sensor.
With the show_rays option, you can see whether or not a target was partially occluded by another object in the simulation (cyan=unobstructed, purple=obstructed).
It is possible to add uniform noise to the blobs, thus matching the characteristics of a real robot better.
For larger swarms it's good practice to selectively toggle the sensor on or off to prevent a performance impact.

## Cameras
A generic multi-camera sensor.
The sensor can be initialized with a number of cameras each running different algorithms for detecting different objects in the simulation.
Can be attached to any composable entity in ARGoS that contains an embodied entity with at least one anchor.
It is possible to draw the frustum of each camera sensor in the OpenGL visualization.
To run an algorithm (led_detector, directional_led_detector, tag_detector) on the camera sensor, simply add the algorithm as a node under the camera node.
Each of the algorithms requires a medium to be present.
With the show_rays option, you can see whether or not a target was partially occluded by another object in the simulation (cyan=unobstructed, purple=obstructed).

## Colored_blob_omnidirectional_camera (rot_z_only)
This sensor accesses an omnidirectional camera that detects colored blobs.
The 'medium' attribute must be set to the id of the leds medium.
With the show_rays option, you can see whether or not a target was partially occluded by another object in the simulation (cyan=unobstructed, purple=obstructed).
It is possible to add uniform noise to the blobs, thus matching the characteristics of a real robot better.
For larger swarms it's good practice to selectively toggle the sensor on or off to prevent a performance impact.

## Colored_blob_perspective_camera
A generic perspective camera sensor to detect colored blobs.
The 'medium' attribute must be set to the id of the leds medium.
With the show_rays option, you can see whether or not a target was partially occluded by another object in the simulation (cyan=unobstructed, purple=obstructed).
It is possible to add uniform noise to the blobs, thus matching the characteristics of a real robot better.

## Ground (rot_z_only)
This sensor accesses a set of ground sensors.
The sensors all return a value between 0 and 1, where 0 means black and 1 means white.
It is possible to add uniform noise to the sensor, thus matching the characteristics of a real robot better.

## Battery
This sensor returns the current battery level of a robot.
This sensor can be used with any robot, since it accesses only the body component.
It is possible to add uniform noise to the sensor, thus matching the characteristics of a real robot better.

## Joints
This sensor is used to monitor the joints inside a prototype entity.