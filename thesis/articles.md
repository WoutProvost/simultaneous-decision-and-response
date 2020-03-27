# Purpose
- Investigate how on a macroscopic level a reaction emerges as a response to the decision.
- Parallel collective decisions that need to be related to each other in a particular time frame. 

# Test environment
- ARGoS simulator
- 2D
- 2 or more options to discover and/or decide upon
- agents can communicate with their immediate neighbours and take individual decisions
- the decision and response fases overlap and thus run parallel to each other
- quality of each option is equal? Since which option is chosen is not important
- A robot colony is in some kind of nest with 2 or more exits, each blocked by a gate. There are 2 kinds of robots: sensors and grippers. The sensors detect temperature (light intensity) and the grippers have the means of opening the gates. There is a fire hazard in the nest, so the swarm must evacuate. Depending on the position of the fire, the swarm decides on one of the exits. In some scenarios the fire might spread dynamically, so that the swarm might need to change its decision.

# Minimum requirements
- individual detection mechanism
- decision detection mechanism
- individual reaction mechanism
- balance between time and accuracy of the reaction

# Challenges
- The detection (by the individual agents) of the decision that the system is adapting collectively ==> quorum?
- The successful trigger and formulation of the proper collective response ==> depends on the task
- Achieving the collective response under the time constraint ==> accuracy-time trade-off

# Other notes
- How a response can build up collectively as a reaction to a specific collective decision, and what parameters will be used to track the evolution of these fases.
- Which task fits best this clause: 'Agents that move in a 2D environment to explore and discover options'
- 'Symmetry-breaking problems, in which the available options are of the same quality and hence, it is not important for which of the options the system decides but that it collectively agrees on one'. So each option is of equal quality.
- Parallelizing the collective response with the collective decision is of a high benefit due to the time constraint.
- Bij schrijven van thesis, bekijk de .h files in de argos repository, de documentatie op de argos website, de command help en de eigen documentatie (want paar dingen aan toegevoegd daar) in de markdown file om meer informatie te krijgen over de actuators, de sensoren, de media en de bots (https://github.com/ilpincy/argos3/tree/master/src/plugins/robots/foot-bot/control_interface). Media en bots bekijken is dus ook belangrijk.
- Vermeld allerlei settings en weggelaten default values vanuit de configuration file.

# Questions and answers
- Simulation using 'sensors' or learning approach using reward systems. See ARGoS.
- What will these sensors sense and or transmit, in other words in what way will the agents detect or announce their presence to the other agents.
- What global goal or task will the simulation use, perhaps the task mentioned on Plato? Foraging with some kind of energy sources? Migrating the nest to a side of the arena?
- How many agents N (scale from lowerbound to upperbound for analysis). 50 to 100 and scale environment => arena size should pack 500 and use 100.
- Communication/voting mechanism? Is this even needed and/or scalable?
- What metrics will be used for analysis and how will the analysis be executed (i.e. what parameters shall be tracked). Last article is a very good example. Degree of coherence, how quick it converges to the decision, how many times it picks the correct decision and response.
- p.4 Rate equation.
- accuracy vs. cohesion
- Case Study I-A, I-B and II are great implementation examples of macroscopic parameterisation and analysis
- How many iterations for analysis => at least 30.
- When do we consider the cohesion a success (100%, 90%, ...), i.e. the quorum and what is the maximum execution time => Significant majority, starting from 80%.
- What parameters do we use to track the emergence of a collective response.
- See **IMPORTANT** tag.

# Other articles to read
- https://www.sciencedirect.com/science/article/pii/B0080430767031107
- https://code.ulb.ac.be/dbfiles/ValHamDor2015aaai.pdf
- https://www.frontiersin.org/articles/10.3389/frobt.2019.00016/full
- https://link.springer.com/article/10.1007/s11721-019-00169-8
- https://pdfs.semanticscholar.org/c418/df1e62079f84744ecc07169281f8fae30ab9.pdf?_ga=2.17994940.403303839.1581080667-1354700671.1581080667
- https://lib.ugent.be/fulltxt/RUG01/002/495/017/RUG01-002495017_2018_0001_AC.pdf
- https://lib.ugent.be/fulltxt/RUG01/002/495/054/RUG01-002495054_2018_0001_AC.pdf
- file:///C:/Users/Wout/Downloads/PAPER_2012_IntJournalRoboticsResearch.pdf
- file:///C:/Users/Wout/Downloads/PAPER_BIOROB_Pisa_2006.pdf

# Information about Autonomous Robots Go Swarming (ARGoS)
Multi-robot systems promise to provide efficient solutions for an ever increasing variety of different applications. It can simulate large-scale swarms of robots of any kind efficiently. You can customize ARGoS easily by adding new plug-ins. Three main requirements. Accuracy: Close similarity of a simulation with respect to reality. Flexibility: The ability to support any kind of robot, and any use case. Efficiency: The ability to optimize the exploitation of computational resources (CPU, memory) so as to achieve the shortest simulation run-time possible. ARGoS allows the user to add functionality in the form of new sensors, actuators, robot components, visualizations, and even new physics engines and new communication means. In ARGoS, physics engines are just a plug-in. The user can choose which physics engine to employ for a simulation.  A medium is a plug-in that implements suitable algorithms to simulate robot communication means. The main simulation loop is distributed across multiple threads. Two types of threads exist: master and slave. The master thread assigns tasks to the slaves. A tasks consists in the update of a single plug-in. The user can set the number of threads as part of the experiment configuration. An important aspect is that parallelism is embedded in the ARGoS core, but it is completely transparent for the plug-in developer. https://www.argos-sim.info/concepts.php

To use ARGoS, you must run the command argos3. This command expects you to provide two kinds of input: An XML configuration file, typically with extension .argos AND user code compiled into one or more libraries. The configuration file contains all the information to set up the arena, the robots, the physics engines, the controllers, etc. User code includes robot controllers and, optionally, hook functions to be executed in various parts of ARGoS to interact with the running experiment.
https://www.argos-sim.info/user_manual.php

Explain file structure and maybe add documentation in code. Use image from user manual.
argos3 -h
argos3 -q plugin_name

# 1. A review of swarm robotics tasks

### **Commonly used tasks:**  (p.292)
Aggregation, flocking, foraging, object clustering and sorting, navigation, path formation, deployment, collaborative manipulation and task allocation. For each task many different implementations, metrics and analytical methods exist.

### **Why we need/want swarm robotics:** (p.292)
The tasks either cannot be accomplished by each individual robot alone, or are carried out more effectively by the robots as a group. Using a multitude of agents to solve a task in a distributed manner allows working with significantly less complex agents at the individual level.

Main motivations for swarm robotics studies: scalability, flexibility and robustness. The capabilities of a single robot (such as sensing, communication and computation capabilities) are limited compared to the difficulty of the collective task. Interactions between swarm members are distributed and do not rely on coordination mechanisms that would hinder scalability. The locality of interactions and communication, which might be seen as a limitation, has a beneficial effect on scalability and robustness of the system.

Flexibility: its capability to adapt to different environment conditions. (p.293)

The expression “swarm intelligence”, which is now widely used in the field of swarm robotics, refers to the superior capabilities of a swarm of agents compared to its single individuals.

### **Disadvantage**: (p.293)
It is often difficult to design the individual robot behavior so that the global performance is maximized. Robots often have a limited and noisy perception of the environment and of the progression of a global task. The distributed nature of the problem makes it difficult to relate individual behavior to global performance.

### **Implementation approaches**: (p.293)
Simulation: virtual environment in which robot capabilities (sensors and actuators) and interactions are simulated by a computer program, allows assessing the performance of a robot swarm with repeated runs of an experiment and facilitates algorithm optimization with a trial-and-error approach.

Modeling: utilizes mathematical formulas to link individual-level control parameters to swarm-level dynamics; with such formulas, the impact of algorithm parameters can be evaluated directly.

Learning: adaptation of algorithm parameters based on previous experience, e.g. artificial evolution. Reinforcement learning is based on a model where robots, which can be in a given set of states and can execute a given set of actions, receive feedback on the results of their actions through a reward; the objective of robots is to choose a mapping between states and actions so as to maximize the reward. Using a local reinforcement paradigm, the reward is assigned only to robots which directly accomplish an objective, while with global reinforcement all the robots are rewarded for each accomplishment.

### **Aggregation**:
The task of gathering a number of autonomous individuals in a common place. (p.294)

Artificial physics approach: is a field of research that models the behavior of individual agents using virtual forces.  Attraction forces (through which different agents tend to stay near each other) and repulsion forces (which prevent collisions between individuals). The force exerted on it by each of its neighbors, which depends on the neighbor distance. (p.294)

Probabilistic approach: the behavior of each robot is determined partially in a random manner, and partially based on its interactions with the surrounding environment. Switching between states using a finite state machine with at least two states (walk and wait). (p.294)

Evolutionary approach: the aggregation dynamics is obtained using robot controllers whose parameters are selected through artificial evolution. Neural networks linking sensory inputs to actuator outputs are a common type of controllers evolved using these methods. Fitness value measuring the ability of a given generation of individuals to accomplish a task. (p.295)

Free aggregation method: robots are given the task of aggregating without any preference for a specific aggregation site. Move randomly in the environment and stop at a given location based on the number of detected neighbors. A higher number of cockroaches corresponding to a higher probability of stopping. Resume random walking at any time, possibly leaving an aggregate. A lower number of cockroaches correspondig to a higher probability of walking. (p.295)

Environment-mediated aggregation method: the location of a given robot in the environment influences the robot behavior, so that aggregation is achieved with higher probability in some defined “preferential” regions. It starts moving randomly until it collides with another honeybee; when a collision occurs, the honeybee stops, and remains stopped for a time duration. (p.296)

What is an "aggregate"? A group of robots such that for any pair of robots in the group there is a path connecting them formed by robots within a maximum distance from each other; the value of the maximum distance is usually chosen based on the range of local communication and sensing of robots. In studies where robots are controlled by a finite state machine, aggregates can be identified by robots whose controller is in the “wait” state. (p.297)

### **Flocking:**
Form large groups of individuals moving together toward a common target location. A fundamental component is the ability to measure the distance and relative orientation of neighboring robots. (p.298)

Three basic rules: collision avoidance, velocity matching and flock centering. (p.299)

Direction by global target method: If the target is known by all robots in the swarm, local interactions between robots serve mainly the purpose of maintaining a compact formation while avoiding collisions. Individual robots calculate a “center of mass”, which represents the desired location to be reached in the short term. Using local interactions, informed robots can propagate the information on the target to the other robots and steer the swarm toward the target. (p.299)

Emergent direction method: flocking can be obtained even in the absence of this information and with individual robots initially moving on random and uncorrelated directions. A swarm-level global direction of movement can emerge from local interactions. (p.299)

A common and intuitive metric is given by the distance covered by the center of mass of the robot swarm, where the center of mass at a given time is calculated as the average of robot positions. If the flocking task is defined so that robots should move toward a global goal direction, performance metrics must incorporate this direction. For example, in various studies the accuracy value measures how the average direction of robots differs from the goal direction, and in the effective traveled distance projects the vector representing the displacement of the center of mass of the swarm on the vector indicating the goal direction. (p.300)

### **Foraging:**
Efficiently exploit food sources using local interactions between individuals. A specific area is designated as the “nest”, and the objective of the swarm is finding items scattered in the environment and bringing them to the nest. (p.300)

A robot is either looking for items in the environment or carrying an item to bring to the nest. In order to achieve cooperation, there must be some form of communication between individuals, so that the actions executed by a robot are influenced by the activity of the rest of the swarm. (p.301)

Shared memory method: all robots in a swarm are able to read and write information on a shared medium. With a shared memory, robots can communicate their recent experience (e.g. the path they followed to reach a given place) and thus help other robots to localize places of interest. Each robot contributes with its imperfect information to build a shared map of the arena. The trail information that is gradually built by foraging robots can be used not only to follow the same trails to reach the same locations, but also to avoid trails used to reach different target locations. (p.301)

Communication through the environment method: produce chemical substances called pheromone and use them to mark the environment. Indirect communication, which uses the environment as a medium for sharing information. (p.301)

Direct communication method: refers to a process where robots exchange information directly between each other, often (but not necessarily) explicitly transmitting data to signal a particular status. Information can be exchanged between nearby robots, which can then act upon received information modifying their behavior to improve the foraging performance. (p.301)

Path formation refers to building one or more “preferential routes” in the foraging arena so that robots either searching for items or carrying an item can reach their current target in an
optimized way. These routes are built incrementally by robots as they execute the foraging activity, and can disappear if the reason for which they were created no longer exists, such as when a source of items is depleted. Robots carrying an item drop “crumbs” on their return path to the nest, while robots searching for items are attracted by crumbs. (p.302)

Cooperative transport focuses on cooperation mechanisms by which the process of moving an item to the nest is made more efficient with the contribution of multiple robots. Items are passed from one robot to another until they reach the nest. Sometimes robots are designated specific areas. (p.302)

### **Object Clustering:**
Objects scattered in the environment must be grouped together. There is not a predefined destination place for collected objects, the goal being to place the objects near each other. When dealing with different kinds of objects this task is often called "sorting". (p.303)

Robots are assumed to be unable to sense the presence of distant objects, thus the typical behavior when searching for objects is to move randomly. (p.303)

Increasing the number of robots employed for a given task can only lead to a sub-linear increase of global performance, due to the possibility of inter-robot interference. Thus, mechanisms of communication between robots are usually not considered in clustering studies. Most existing literature on clustering and sorting tasks makes use of simple robots with no localization capabilities, where clustering of objects emerges as a mere result of probabilistic interactions with the environment. (p.304)

If robots are endowed with the capability to localize themselves in the environment, the clustering activity can be performed more efficiently, by moving encountered objects to a fixed location instead of relying on probabilistic approaches. While initially each robot may select an arbitrary location and begin clustering in that location, during task execution all robots must eventually converge to a single, shared cluster by either communicating its own cluster location or by measuring the size of different clusters. (p.305)

### **Navigation:**
A robot with limited sensing and localization capabilities is able to reach a target in an unknown location with the help of other robots. The target location needs to be reached by a single robot. (p.306)

Each robot in a swarm has a limited knowledge of the local environment in which it operates, so the key to a successful navigation strategy in a multi-robot scenario is sharing knowledge between robots. Such knowledge usually consists of an estimate of the distance to the target, which can be expressed as Euclidean distance, as a “hop count”, or through some other means. (p.306)

Robots could form a grid of interconnected nodes which can guide an agent to an unknown target location, just like a standard routing protocol. This routing could happen statically or dynamically as the robot is moving towards the target. (p.306)

### **Path Information:**
Robots are able to build collectively a path between two locations in the environment, so that the time needed to reach one location from the other is minimized. (p.307)

A stationary robot chain is formed when one target location is connected to the other through a sequence of robots, where each robot in the chain is within sensing or communication range of its two neighbors. A robot that is not part of the chain can move from one location to the other by simply following the sequence of stationary robots. (p.308)

Path formation doesn't necessarily require the continuous presence of stationary robots “marking” the path. Another approach uses a positive feedback mechanism triggered by robots moving repeatedly between the two target locations, so that a robot following a path at a given time increases the likelihood that other robots will follow the same (or a similar) path in the future. (p.308)

### **Deployment:**
Robots must deploy themselves in an environment without central coordination. (p.309)

Direct communication method: communication can take place using explicit messages, or implicitly, by sensing the nearby presence and relative position of other robots (p.309)

Stigmergy communication method: gives robots moving in an area of the environment an indication of the actions done previously by other robots in the same area. An action done by a robot increases the probability that the same action is repeated by other robots.  Conversely, preventing different robots from repeating the same action, and specifically preventing the same areas of the environment from being explored multiple times. Using simulated pheromone traces: the presence and intensity of pheromone at a given location is used as an indication that the location has been visited before. In some studies, pheromone is assumed to evaporate over time. (p.309)

In the dispersion task, swarm members must position themselves away from one another, with the objective of maximizing the area covered globally by the swarm. (p.309)

If the total number of robots is not sufficiently high to cover the entire arena, this model can be complemented by a “guided growth” model, such as when one robot starts to move away from the swarm to explore uncovered areas of the arena and doing so “pulls” the entire swarm, because the other robots follow the exploring robot in order to keep connectivity with it and between each other. Each robot must stay within communication range of a minimum number of other robots. (p.310)

Pattern formation is a variant of the deployment task where robots occupy relative positions such that when viewed globally their ensemble can be described by a specific pattern. (p.310)

### **Collaborative Manipulation:**
In some instances, the task at hand cannot be executed by any single individual, but requires cooperation between multiple individuals. (p.311)

Robots engaging in behaviors seemingly unrelated to the task at hand. For example, in a simple follow behavior in which a robot is attracted by other robots moving in front of it modifies the otherwise random distribution of robots in the arena so that robots are able to cooperatively push a box. In case of a stall where all robots are waiting for other robots, robots can abandon the object they found and restart searching for other objects with a potentially higher number of nearby robots. (p.311)

Without a preferred direction, different robots may push the box from different angles, thus negatively interfering with each other. A group of robots must find a box located in the arena and push it at one edge of the arena. If there is a predefined goal location to which the box must be moved, and if robots are able to determine the direction toward the goal, this negative interference can be avoided. (p.311)

When a robot encounters an object to be manipulated, it stops near the object and waits for other robots to arrive; if the number of robots required to execute the task arrive within a certain amount of time, then the task can be completed successfully, otherwise the robots near the object time out and restart moving in search of other objects to be manipulated. The rate of successful task execution thus depends on various factors such as robot and object density in the arena, number of required robots for a single manipulation, and the time robots wait before deciding to abandon an object. (p.312)

### **Task Allocation:**
The ability to dynamically change the task executed by each robot based on local perception of the environment. Adapting the ratio of robots engaged in a given task (or not
engaged in any task) based on the current demand for the task. (p.313)

Threshold-based method:  robots observe a given quantity in the environment and change their activity when this quantity reaches a threshold value. Local quantities and/or variable thresholds are generally preferred over global ones to prevent a high number of robots
switching activity at the same time when the threshold is crossed. (p.313)

Probabilistic method: the decision of each robot to switch activities at any given time is taken randomly, with a probability value which is usually changed dynamically based on environment observations. The random component in the control algorithm of each robot prevents a large number of robots from switching activities at the same time. (p.313)

In the foraging scenario, task allocation has been used mainly as a mechanism to determine when each robot should engage in the foraging activity and when it should rest. (p.313)

In a foraging scenario, the stimulus is usually determined by the amount of food or energy in the nest: since the amount of food decreases with time if no robots bring new food to the nest, the corresponding increase of stimulus activates the foraging activity in resting robots, which will likely result in a future increase of food at the nest and a corresponding decrease of stimulus. (p.314)

### **Other tasks:**
Odor Source Localizaition: finding the source of an odor in the environment. A robot detecting the odor signals this event, and other robots in its proximity in the downwind direction move toward the first robot. (p.315)

Object Assembly: a swarm is tasked with building structures from objects located in the environment. Compared to the object clustering task, construction tasks focus on specific spatial relationships between adjacent objects, so that the assembled structure has a defined shape. (p.315)

Self-assembly and Morphogenesis: physically connect to each other utilizing only local interactions. (p.315) Morphogenesis is an extension of the self-assembly concept that allows modular robotic structures to assume specific shapes: each robot joining the structure attaches to it at a position and orientation such that the desired shape is gradually built. (p.316)

Coordinated Motion: In order to allow a modular robotic structure to move efficiently in the environment, part or all of its constituent robots must coordinate to move on a common direction. (p.316)

Group Size Estimations: In different applications where multiple agents are grouped together, knowledge of the group size by each agent can be useful, for example to regulate the group size based on task-specific criteria. (p.316)

Distributed Rendezvous: Agreeing on a single location at which all robots must converge. (p.316)

**IMPORTANT**
Collective Decision-making: the swarm dynamics leads to a group of robots to converge to a unanimous decision; this happens when the different options available to each robot are associated to different rewards (even if robots cannot measure directly the reward associated to each option), but also in the case of options with the same utility.
Different implementations:
- A mechanism for decision-making based on the majority rule opinion formation model, where robots agree on a common decision by applying a local majority rule to small groups; if a latency period is introduced after each robot takes a decision, during which the robot cannot be influenced by other robots, and if the duration of this period depends on the decision being taken (differential latency), then a global consensus is achieved by the swarm on the decision associated with the lowest latency.
- Global consensus on the fastest action is achieved with robots entering an observation state, where they exchange their current preferred action, after each action execution.
- Robots that must agree on a site selection transmit their preference to neighboring robots for a time duration proportional to the perceived quality of the site associated to their current preference.
- The behavior of each robot is a combination of the tendency to reach a specific goal (if the robot is informed about the goal) and the tendency to follow the average behavior of its neighbors. The relative weight given to these two components is changed dynamically based on the local consensus observed from neighboring robots, the swarm can converge to a collective decision even in the presence of informed agents with conflicting goals. (p.316)

Human-swarm Interaction: Allow humans to interact locally with single or small groups of robots or with the environment. A human could take manual control of an agent to influce the behaviour of the swarm. (p.317)

# 2. A Review of Probabilistic Macroscopic Models for Swarm Robotic Systems
The collective behavior of swarms is statistically predictable and has often a simple probabilistic description. Collective (or macroscopic) behavior emerges from individual (or microscopic) decisions robots make. These decisions are based on purely local information that comes from other robots as well as the environment.
- Scalability: the control architecture can be kept exactly the same from a few units to thousands of units.
- Flexibility: units can be dynamically added or removed, they can be given the ability to reallocate and redistribute themselves in a self-organized way.
- Robustness: the resulting collective system is robust not only through unit redundancy but also through unit simplicity and an appropriate balance between exploitative and exploratory behavior. (p.1)

Understanding the effect individual robot characteristics have on the collective behavior. In the past, few analysis tools have been available to researchers. Though simulations are much faster and much more reliable than experiments, their results are not easily generalizable. Simulations do not scale well with the system size — unless computation is performed in parallel, the greater the number of agents, the longer it takes to obtain results. Macroscopic modeling and mathematical analysis offer an alternative to experiments and simulations. (p.2)

Reactive control: robots decide about future actions based solely on input from sensors (including communication with other robots) and the action they are currently executing. Such robots can be represented as stochastic Markov processes. An equation, known as the Rate Equation, describes the dynamics of their collective behavior. (p.2)

### **Microscopic model:**
Microscopic descriptions treat the robot as the fundamental unit of the model. These models describe the robot’s interactions with other robots and the environment. Solving or simulating a system composed of many such agents gives researchers an understanding of the global behavior of the system. The robot’s interactions with other robots and the environment are modeled as a series of stochastic events, with probabilities determined by simple geometric considerations and systematic experiments with one or two real robots. (p.3)

### **Macroscopic model:**
Directly describes the collective behavior of the robotic swarm. It is computationally efficient because it uses fewer variables. Rather than account for the inherent variability of individuals, scientists model the behavior of some average quantity that represents the system they are studying. Such models do not reproduce the results of a single experiment — rather, the behavior of some observable averaged over many experiments or observations. (p.3)

### **Stochastic approach:**
Even if all the forces are known in advance, the robots are still subject to random events: fluctuations in the environment, as well as noise in the robot’s sensors and actuators. A robot will interact with other robots whose exact trajectories are equally complex, making it impossible to know which robots will come in contact with one another. In summary, the behavior of robots in a swarm is so complex, it is best described probabilistically, as a stochastic process. (p.3)

Transitions between states are triggered by external stimuli. This robot can be described as a stochastic Markov process and a state diagram as the Finite State Automaton (FSA) of the controller. A Markov process’s future state depends only on its present state and none of the past states. (p.4)

### **Rate equation:**
Let `p(n, t)` be the probability robot is in state `n` at time `t`. Change in probability density `∆p(n, t) = p(n, t + ∆t) − p(n, t)`. The quantity `p(n, t)` also describes a macroscopic variable — the fraction of robots in state `n`. `Nn(t)` is the average number of robots in state `n` at time `t`. (p.4)

The number of robots in state n will increase in time due to transitions to state n from other states, and it will decrease in time due to the transitions from state n to other states. Rate Equations are deterministic. In stochastic systems, however, they describe the dynamics of average quantities. In a small system, the experiment may be repeated many times to average out the effect of fluctuations. (p.5)

### **Model construction:¨**
To facilitate the analysis, we begin by drawing the macroscopic state diagram of the system. "The collective behavior of the swarm is captured by an FSA that is functionally identical to the individual robot FSA, except that each state of the automaton now represents the number of robots executing that action". (p.5)

Considering several related actions or behaviors as a single state. For example, we may take the searching state of robots to consist of the actions wander in the arena, detect objects and avoid obstacles. We are often interested in the minimal model that captures the important behavior of the system. (p.5)

Each state in the automaton becomes a dynamic variable `Nn(t)`, with its own Rate Equation. Every transition will be accounted for by a term in the equation: a positive term for the incident `(W(n|n)Nn)` arrows and negative term for the outgoing `(W(n|n)Nn)` arrows.  The transition is triggered by some stimulus — be it another robot in a particular state, an object to be picked up, etc. In order to compute the transition rates, we assume, for simplicity, that robots and stimuli are uniformly distributed. The transition rates then have the following form: `W(n|n) ≈ M`, where M is the environmental stimulus encountered. The transition rates can be calculated from first principles, or left as parameters of the model. (p.5)

### **Collaborative stick pulling:**
Locate sticks scattered around the arena and pull them out of their holes. A single robot cannot complete the task on its own: rather, when a robot finds a stick, it lifts it partially out of the hole and waits for a period specified by its gripping time parameter for a second robot to find it. If a second robot finds the first during this time interval, it will pull the stick out; otherwise, the first robot releases the stick and returns to the searching state. A metric for analysis could be the collaboration rate, the rate at which robots pull sticks out, as a function of the individual robot gripping time parameter. (p.6)

### **Collective object collection:**
In the aggregation experiments, the task was to gather small objects in a single cluster starting from a situation where they were all randomly scattered in an arena. (p.6)

Interference is a critical issue in swarm robotics, in particular in foraging experiments where there is a spatial bottleneck at the predefined “home” region where the collected objects must be delivered. When two robots find themselves within sensing distance of one another, they will execute obstacle avoidance maneuvers. Because this behavior takes time, interference decreases robots’ efficiency. (p.7)

### **Discussion:**
In order to construct a description of the behavior of a swarm, we do not need to know the exact trajectories of every robot; instead, we derive a model that governs the dynamics of the aggregate, or average, swarm behavior. First, we assume that robot’s actions are largely independent of one another (dilute limit), and the transition rates can be represented by aggregate quantities that are spatially uniform and independent of individual robots or their trajectories. Second, up to date we considered exclusively nonspatial metrics for evaluating collective swarm performance. As long as detection areas do not overlap between the objects placed in the arena and the metric does not specifically address spatiality, these assumptions are correct. Third, we assumed that modeled robots have perfectly centered, uniform, and precise range of detection for each object they may encounter in the arena. Fourth, modeled robots are characterized by a set of parameters, each of them representing the mean value of some real robot feature: mean speed, mean duration for performing a certain maneuver, and so on. Fifth, further difficulties may arise due to behavioral granularity captured in the models. Certain controllers can be approximated by a FSA, though certain routines (p.8)

### **Conclusion:**
The behavior of each robot is inherently probabilistic in nature and often not completely predictable, and its future state depends only on its present state. Rate Equations describe how the average collective system properties change in time. These equations can be easily written down from the details of the individual robot controller. Analysis yields important insights into the system, such as what are the important parameters that determine the behavior, how to optimize swarm performance, etc. (p.9)

# 3. Swarm robotics: a review from the swarm engineering perspective

### **What is 'Swarm Robotics'?**
“A novel approach to the coordination of large numbers of robots.”
“The study of how large numbers of relatively simple physically embodied agents can be designed such that a desired collective behavior emerges from the local interactions among agents and between the agents and the environment.” - Sahin (p.1)

The behavior of groups of social animals appear to be robust, scalable, and flexible.
- Robustness: the ability to cope with the loss of individuals. Redundancy and the absence of a leader.
- Scalability: the ability to perform well with different group sizes. Local sensing and communication instead of global.
- Flexibility: the ability to cope with a broad spectrum of different environments and tasks. (p.2)

### **What are the main characteristics and/or requirements that differentiate swarm robotics from other multi-robot approaches?** (p.2)
- robots are autonomous
- robots are situated in the environment and can act to modify it
- robots’ sensing and communication capabilities are local
- robots do not have access to centralized control and/or to global knowledge
- robots cooperate to tackle a given task

### **What is 'Swarm Engineering'?** (p.2)
“The design of predictable, controllable swarms with well-defined global goals and provable minimal conditions.”
“The swarm will do precisely what it is designed to do, and that it will do so reliably and on time.” - Kazadi

## Design

### **Behaviour-based design method:**
Still no formal or precise ways to design individual level behaviors that produce the desired collective behavior. The intuition of the human designer is still the main ingredient. In an iterative way, the individual behavior of each robot is implemented, studied, and improved until the desired collective behavior is obtained. In behavior-based design, inspiration is often taken from the observation of the behaviors of social animals. (p.4)

Usually a trial and error process: individual behaviors are iteratively adjusted and tuned until the resulting collective behavior is obtained. Bottom-up. Two main categories: probabilistic finite state machine design, virtual physics-based design. (p.5)

### **Probabilistic finite state machine design:**
Does not plan its future actions, but it takes decisions only on the basis of its sensory inputs and/or its internal memory. The transition probability between states is fixed when a single probability value is defined and used throughout the execution of the collective behavior. The transition probability is not fixed when it is defined through a mathematical function (response threshold function) of one or more parameters of the system. (p.5)

### **Virtual physics-based design:**
Each robot is considered as a virtual particle that exerts virtual forces on other robots. The robots are able to perceive and distinguish neighboring robots and obstacles, and to estimate their distance and relative position. Each robot computes a virtual force vector (zie formule in artikel). A single mathematical rule smoothly translates the entire sensory inputs space into the actuators output space without the need for multiple rules or behaviors. The obtained behaviors can be combined using vectorial operations. (p.6)

### **Other behavior-based design methods:**
Top-down method using logic formulas (properties) which need to hold true in the final system. In the first step, the properties are defined. In the second step, a macroscopic model is produced. A model checker is then used to verify that the properties hold true in the produced model. In the third step, the macroscopic model is used to guide the process of implementing the system using a simulator. Finally, in the fourth the system is tested using real robots. (p.7)

### **Automatic design method:**
The automatic generation of behaviors without the explicit intervention of the developer. Two main categories: reinforcement learning and evolutionary robotics. (p.7)

### **Reinforcement learning:**
An agent learns a behavior through trial-and-error interactions with an environment and by receiving positive and negative feedback for its actions. The goal of the robot is to learn automatically an optimal policy. The behavior is optimal in the sense that it maximizes the rewards received from the environment. (p.7)

The swarm engineer tackles the task at the collective level, but learning typically takes place at the individual level. The main issue is the decomposition of the global reward into individual rewards. 'Spatial credit assignment'. Other problems are the size of the state space and the incomplete environment perception. (p.8)

### **Evolutionary robotics:**
Inspired by the Darwinian principle of natural selection and evolution. At the beginning, a population of individual behaviors is generated at random. In each iteration, a number of experiments for each individual behavior is executed. In each experiment, a fitness function is used to evaluate the collective behavior of the swarm resulting from that individual behavior. At this point, a selection of the highest scoring individual behaviors are modified by genetic operators, such as cross-over and mutation, and used for the subsequent iterations. (p.8)

Used to find the parameters of an artificial neural network. The same problems identified by us in the application of RL to swarm robotics apply also to ER. Neural networks are black-box and it is often very difficult to understand their behavior. (p.9)

## Analysis

### **Microscopic:**
**IMPORTANT**
Take into account each robot individually, analyzing both robot-to-robot and robot-to-environment interactions. These individual behavior models are mainly used for design purposes. As such they have already been presented in the previous section on behaviour-based design. Microscopic models in which the elements composing a system are simulated with the
use of a computer are traditionally called simulations. (p.10)

### **Macroscopic:**
The individual elements of the systems are not taken into account in favor of a description of the system at a higher level. At least two main categories. (p.10)

### **Rate and differential equations:**
Rate equations describe the time evolution of the proportion of robots in a particular state over the total number of robots. They can be used to derive a macroscopic model of a collective behavior, starting from an individual-level PFSM. First, a set of variables is defined. Usually, one variable is defined for each state and used to track the proportion of the robots in the corresponding states. Second, for each variable, an (rate) equation is defined. The rate equation contains a set of parameters, one for each input and output transition of the corresponding state. The main advantage of the rate equation approach is that it is a systematic method to translate microscopic models into macroscopic models. Its main limit is that, in general, it is difficult to model space and time: robots’ positions in space are not explicitly modeled and discrete time is usually assumed. (p.11)

In the case of a robot, the deterministic component of the Langevin equation models the deterministic motion of the robot influenced by its individual behavior, whereas the stochastic part models the interaction of the robot with the other robots (considered as a flow) and with the environment. (p.12)

### **Classical control and stability theory:**
These are used to prove properties of the swarm. (p.12)

Two properties of the system: safety and liveness. The safety property is verified when the robots do not exhibit undesirable behaviors. The liveness property is verified when the swarm dynamics actually do evolve over time. (p.13)

### **Real-robot analysis:**
It is practically unfeasible to simulate all the aspects of reality using simulations. Experiments with real robots help to test the robustness of swarm robotics systems that have noisy sensors and actuators. The experiments are performed in controlled environments. By controlled environments we mean artificial arenas in which most conditions—e.g., light intensity, radio interference and floor smoothness—can be controlled by the experimenter. This is often very far from the scenarios in which swarm robotics systems are supposed to operate. It would help to clarify possible differences between the model and the real-robot system. (p.14)

## Spatially-organizing behaviours
Collective behaviors that focus on how to organize and distribute robots and objects in space. For each of the following tasks, images are available in the artikel. (p.15)

### **Aggregation:**
Group all the robots of a swarm in a region of the environment. It also allows a swarm of robots to get sufficiently close one another so that they can interact. Using PFSMs, the robots explore an environment and, when they find other robots, they decide stochastically whether to join or leave the aggregate. Using artificial evolution, the parameters of a neural network are automatically selected in order to obtain an aggregation behavior. (p.15)

### **Pattern information:**
Deploying robots in a regular and repetitive manner in order to create a desired pattern. The most common way to develop pattern formation behaviors in robot swarms uses virtual physics-based forces to coordinate the movements of robots. (p.16)

### **Chain formation:**
Robots have to position themselves in order to connect two points. The chain that they form can then be used as a guide for navigation or for surveillance. The most used design approaches are probabilistic finite state machines (PFSMs), virtual physics-based design and artificial evolution. (p.17)

In the explorer role, the robots are searching for chain members or for the goal area. When they find either a chain member or the goal, they switch to the chain member role and stop. Chain members can become explorer again according to a probability that increases over time if no other robots are perceived. (p.18)

### **Self-assembly and morphogenesis:**
Self-assembly is the process by which robots physically connect to each other. Morphogenesis is the process that leads a swarm of robots to self-assemble following a particular pattern, and can be used by the swarm to self-assemble into a structure that is particularly appropriate for a given task. With ants this taks can be used to float on water. (p.18)

Such robots are able, when connected, to share energy and computational resources with their neighbors. (p.19)

### Object clustering and assembling:**
To group objects close one to the other. The difference between clusters and assembles is that clusters are composed of non-connected objects, whereas assembles are composed of physically linked objects. Using probabilistic finite state machines. The robots explore the environment at random and react in different ways to the discovery of available objects or of part of the cluster/assemble to create. (p.20)

## Navigation behaviours
Behaviors that cope with the problem of coordinating the movements of a swarm of robots. (p.21)

### **Collective exploration:**
The goal of area coverage is to deploy robots in an environment in order to create a regular or irregular grid of communicating robots. The obtained grid can be employed, for example, to monitor the environment for hazardous leaks or to guide other robots. We call the behavior necessary to guide the navigation of other robots swarm-guided navigation. (p.21)

The most common way to tackle area coverage is to use virtual physics-based design to obtain a grid covering the environment. This approach allows the robots to maximize the area covered and form a connected communication network. (p.22)

Similarly to what happens in packet routing, the robots keep a table of the distance of other robots with respect to the target. A robot can then use the entries in the table and reach the target. (p.23)

### **Coordinated motion:**
Also known as flocking, robots move in formation similarly to schools of fish or flocks of birds. Animals gain several advantages, such as a higher survival rate, more precise navigation and reduced energy consumption. Coordinated motion behaviors are usually based on virtual physics-based design. Robots are supposed to keep a constant distance from one another and an uniform alignment while moving. Three simple rules: collision avoidance, velocity matching and flock centering. Collision avoidance keeps the individuals from colliding one with the other. Velocity matching ensures that each individual matches the speed of its neighbors and flocking centering forces each individual to stay close to its neighbors. (p.23)

### **Collective transport:**
Also known as group prey retrieval, is a collective behavior in which a group of robots has to cooperate in order to transport an object. In general, the object is heavy and cannot be moved by a single robot, making cooperation necessary. The robots need to agree on a common direction in order to effectively move the object towards a target. Using probabilistic finite state machines or artificial evolution. Cooperation is obtained either through explicit communication of the desired motion direction, or through indirect communication, that is, by measuring the force applied to the carried object by the other robots. (p.25)

## Collective decision-making
**IMPORTANT**
Deals with how robots influence each other when making choices. It can be used to answer two opposite needs: agreement and specialization. A typical example of agreement in swarm robotics systems is consensus achievement. The desired outcome of consensus achievement is that all the robots of the swarm eventually converge towards a single decision among the possible alternatives. A typical example of specialization, instead, is task allocation. The desired outcome of task allocation is that the robots of the swarm distribute themselves over the different possible tasks in order to maximize the performance of a system. (p.26)

### **Consensus achievement:**
A collective behavior used to allow a swarm of robots to reach consensus on one choice among different alternatives. The choice is usually the one that maximize the performance of the system. Consensus is generally difficult to achieve in swarm of robots due to the fact that very often the best choice may change over time or may not be evident to the robots due to their limited sensing capabilities. Ants are able to decide between the shortest of two paths using pheromones. Bees have mechanisms to collectively decide which is the best foraging area or which is the best nest location among several possibilities. In the first category, direct communication is used: each robot is able to communicate its preferred choice or some related information (routing? scalability? local broadcast?). In the second category, instead, indirect communication is used: the decision is performed through some indirect clues, such as the density of the robot population. (p.26)

In the first, the robots simply follow the robot closest to a target, resulting in a decision based on the spatial distribution of the swarm; in the second, the robots vote, using a majority rule, to decide which target to follow. (p.27)

A strategy for consensus achievement through direct communication in a swarm of robots performing foraging. The robots are able to decide between two foraging areas. When two robots get close, they exchange their measured distances between the nest and the latest visited goal. Each robot performs an average of its measured distance with the one received from the other robots. In this way, the robots are able to agree on which area is the closest to the nest and discard the other one even when the measured distances are noisy. (p.27)

When a robot finds a new alternative, it evaluates its quality and sends recruiting messages to other robots to advertise it. The frequency of these messages is proportional to the perceived quality of the alternative. Thanks to the different message frequencies associated with the different alternatives, over time all robots converge on the best alternative. The behavior is implemented as a probabilistic finite state machine. (p.27)

Each individual robot has a preferred path. When a group of three robots is formed in the nest, the robots choose the path that is preferred by the majority of them. The chosen path becomes the preferred one for all the robots in the group. Since the robots choosing the short path take less time to complete the execution, they are more often in the nest. This results in more groups formed by robots preferring the short path than those preferring the long path. This asymmetry eventually makes the robots use the shortest path. (p.27)

### **Task allocation:**
Behavior in which robots distribute themselves over different tasks. The goal is to maximize the performance of the system by letting the robots dynamically choose which task to perform. In ant or bee colonies, part of the swarm can perform foraging while another part looks after the larvae. Task allocation is not fixed but can change over time. Mainly obtained through the use of probabilistic finite state machines. To promote specialization, the probabilities of selecting one of the available tasks are either different among the robots or they can change in response to task execution or messages from other robots. (p.28)

Robots have to collect prey that are then converted into energy in the nest. While foraging, the robots consume energy. To replenish this energy, the robots can draw it from a common reservoir. Each robot decides to leave and collect prey or to stay in the nest according to a probability. This probability depends on whether the nest energy is above or below a given threshold. Since this threshold is not homogeneous in the swarm, the number of robots allocated to foraging or to resting is a function of the energy level of the nest. (p.28)

Robots must remove sticks scattered in the environment. To remove a stick, two robots must cooperate performing two parts of the task: one holds a stick from the top and the other from the bottom. Once a robot finds a stick, it holds its top and waits for another robot to complete the second part of the task. If after a certain waiting time no one helped, the robot leaves the stick and searches for another one. This waiting time is changed dynamically according to how well a robot performed in the past. Although the results were not conclusive, the authors observed that, over time, the robots develop a preference for one of the two parts of the tasks, specializing in robots holding the top part of a stick and robots holding the bottom part. (p.29)

## Other collective behaviours

### Collective fault detection
Hardware failures are still quite common. Techniques to allow robots to autonomously detect failures and faulty behaviors have been developed by exploiting the natural redundancy of swarm robotic systems. (p.29)

### Group size regulation
creating or selecting a group of a desired size. An excessive number of robots can reduce the performance of a system. (p.30)

### Human-swarm interaction
Since there is neither a leader nor centralized control, the operator does not have a simple way to control the behavior of the system. Human–swarm interaction studies how a human operator can control a swarm and receive feedback information from it. A human operator could use a central computer to select and control a subgroup of robots. The second approach is based on local interactions: the human operator places pre-programmed beacons in the environment. Such beacons are used to communicate a new behavior to the robots which are in their communication range. (p.30)

## Conclusion: limits and future directions
Swarm robotics has several possible applications, including: exploration, surveillance, search and rescue, humanitarian demining, intrusion tracking, cleaning, inspection and transportation of large objects. With an increasing use of swarm robotics systems, we envision an increasing need for a swarm engineering. (p.31)

### **Requirement modeling and specification:**
We foresee an increasing need for well-defined processes to help in requirement gathering and for formal languages to help in requirement specification. (p.32)

**Design and realization:**
The lack of methods for the top-down design of collective behaviors. A lot of domain knowledge is still required to tackle medium to complex applications. (p.32)

**Verification and validation:**
Despite the great number of analysis methods, performing verification and validation of a swarm robotics system and comparing one system with another are still very difficult tasks. The reason behind this is the lack of well-defined metrics and testbed applications. Very often, metrics are too tightly related to a specific solution and thus cannot be reused for other systems or for comparisons. (p.32)

**Operation and maintenance:**
Require less manual intervention because of their robustness, scalability and flexibility. Although these three characteristics might reduce the need for maintenance, this might be true only up to a given extent. Further studies are necessary to understand when and how to perform maintenance on a swarm robotics system. Regarding human-swarm interaction, it might be difficult to stop a swarm that is behaving in an unpredicted or dangerous way. (p.32)

# 4. Collective decision-making
**IMPORTANT**

### **What is collective decision-making?** (p.30)
How groups reach decisions without centralised leadership. All individuals seek to agree
on the same outcome. Within high-relatedness groups, group members’ behaviour is shaped as part of a group-level decision-making mechanism. Within unrelated groups, individuals’ behaviour should maximise their own expected fitness, within the context of the group.

### **Decision Accuracy:** (p.30)
There is an inherent decision-making trade-off between true positive rate and false positive rate; a decision-maker cannot improve the rate at which they detect events of interest, without also increasing the rate at which they incorrectly detect those events when they have not happened. Yet in the group situation, a quorum decision rule, typical of social insect colonies, allows the group to simultaneously improve both rates. Group decisions are always more accurate than individual decisions. This has led to a speed-accuracy tradeoff.

### **Value-based Decisions:** (p.31)
Obviously, it is advantageous for the collective of bees to choose the site of highest possible quality. Two potential nestsites available, both of equal but low quality. In this case it is best to wait and postpone the decision until another option will be discovered. If there are two alternatives having equal but high qualities, then the honeybees should choose as quickly as possible. This has led to a speed-value tradeoff.

Value may refer to stimulus intensity, or to reward magnitude. Increasing the magnitudes of two input signals while keeping their difference or ratio constant leads to faster responses. A speed-value tradeoff should play a key role in decision-making that is not about ‘correct’ or ‘false’ but rather requires a strategy to choose the best alternative among available options.

### **Nutrition and Decision-making:**
Foraging decisions often aim at balancing the intake of different nutrients rather than maximising the gain in energy. Nutritional deficits may bias or shape decision-making. The nutrient space is an N-dimensional space, which is spanned by N axes each of which represents one nutrient required in the diet. The performance of the animal or social insects can then be evaluated by plotting the deficits in proteins and in carbohydrates on the axes of a two-dimensional Cartesian coordinate plane. (p.31)

Fulfil an ongoing decision task by selecting repeatedly among two alternatives, to bring their internal state as close as possible to their target intake. This behaviour can be tracked in nutrient space. Deficits in one or more nutrients drive the motivations for deciding for or against an action that reduces a deficit. Being central to all social groups, nutritional interactions may have contributed to the evolution of social behaviour. (p.32)

### **Robots and Collective Behaviour:** (p.32)
Swarm robotics, where a large number of autonomous robots coordinate with each other to perform a common task. Each individual gathers and exchanges information with the environment and peers in a local range. Look at natural processes that display the desired behaviour and adapt such processes to implement multirobot systems. In collective behaviour, the process dynamics are principally determined by how information is acquired, processed and transferred between individuals.

Working with a physical device imposes constraints that force the designer to consider the limited capabilities of each individual (in terms of sensors and actuators), the effect of noise, and the mechanistic process of information transfer. As a result, a robot implementation reduces the possibility of oversimplifying the model and can provide insights into biological mechanisms.

# 5. A Design Pattern for Decentralised Decision-making
**IMPORTANT**
Design patterns provide formal guidelines to deal with recurring problems in a specific field. For distributed systems, design patterns prescribe the individual-level microscopic behaviour required to obtain desired system-level macroscopic properties. In this paper, we propose a design pattern for decentralised decision-making based on the nest-site selection behaviour of honeybee swarms. (p.2)

### **Cross inhibition:**
A best-of-n decision problem, that is, the choice of the best option among `n` different alternatives. Each option `i` is characterised by a quality `v_i`. We have a population `A` of `N` agents where each agent `a_g` is either committed to one of the available options `i` and belongs to the sub-population `A_i` of `N_i` agents and thus fraction `W_i = N_i/N` of the entire population, or is uncommitted and belongs to sub-population `U` with `N_U` agents and thus fraction `W_U = N_U/N` of the entire population. Agents can obtain a noisy estimate `^v_i` of the quality associated to option `i`. At the macroscopic level, a decision is taken as soon as the entire population, or a large fraction `W_q` (quorum) is committed to a single option. A macroscopic model that accounts for the system meanfield dynamics, and that describes the decision process at the population level. A microscopic model in the form of a probabilistic finite state machine (PFSM) to describe the behaviour of the individual agent that changes its commitment state in response to probabilistic events. (p.2)

### **Macroscopic model:**
We can identify at least 4 processes:
- uncommitted agents spontaneously discover option `i` at rate `γ_i`.
- agents committed to option `i` spontaneously abandon commitment at rate `α_i`.
- agents committed to option `i` recruit uncommitted agents at rate `ρ_i`.
- cross inhibition: agents committed to option `j != i` inhibit agents committed to option `i` at rate `σ_j`. A committed agent that receives an inhibitory signal stops recruiting and reverts to the uncommitted state, becoming available for discovery or recruitment by other agents, which breaks decision deadlocks in case of equal-best options. (p.3)

This leads to the following equations:
- `W_i = γ_i*W_U - α_i*W_i + ρ_i*W_i*W_U - SUM(j!=i){σ_j*W_i*W_j}`
- `W_U = 1 - SUM(i){W_i}`

Here, the variation of `W_i` is determined by the four processes described above. All four transition rates are functions of the quality `v_i`:
- `γ_i = f_γ(v_i)`
- `α_i = f_α(v_i)`
- `ρ_i = f_ρ(v_i)`
- `σ_j = f_σ(v_i)`

### **Microscopic model:**
The behaviour of individual agents is represented by the probabilistic finite state machine (PFSM) shown in (zie figuur artikel) that describes the commitment dynamics. An agent can be either uncommitted (state `C_U`) or committed to option `i` (state `C_i`), and probabilistically changes state every `τ` seconds according to two types of transitions: spontaneous and interactive. (p.3)

Spontaneous transitions model the discovery of option `i` with probability `P_γ(v_i)` and the abandonment of commitment to option `i` with probability `P_α(v_i)`. (p.3)

Interactive transitions model the recruitment and cross-inhibition processes resulting from the interaction between agents belonging to different populations. The probability of any agent interacting with an agent committed to option `i` as `P_W_i = N_i/N`. Recruitment for option `i` is modelled by a transition from `W_U` to `W_i` with overall probability `P_W_i*P_ρ(v_i)`. Cross-inhibition of an agent committed to option i is instead modelled as the cumulative effect of the interaction with agents committed to a different option, with overall probability `SUM(j!=i){P_W_i*P_σ(v_j)}`. Zie tekening voor visuele representatie. (p.3)

### **Micro-macro link:**
In the homogeneous case, all agents compute their transition probabilities in the same way as a function of the estimated quality `^v_i`. `P_λ,g` represents the actual probability for the agent `a_g` to undergo one of the four transitions `λ`, thus `P_λ,g(^v_i) = λ_i*τ = f_λ(^v_i)*τ`. Hence, a principled choice of the individual transition probabilities can be made to obtain the desired macroscopic dynamics as defined in the last section of 'Macroscopic model'. (p.4)

In the heterogeneous case, each agent computes its own transition probabilities differently
from other agents. A simple response threshold scheme, so that agent `a_g` follows a transition with a fixed probability if the (estimated) option quality `^v_i` exceeds a given threshold `δ_g`. `P_λ,g` grows with amount `P_λ_u` and shrinks with amount `P_λ_d` which are tunable parameters. The threshold is drawn for each agent from a probability distribution `D_λ` through the cumulative distribution function `F_D_λ` (zie artikel voor formule). This leads to `P_λ_u = f_λ(v_M)*τ` and `P_λ_d = f_λ(v_m)*τ` for `v_M` being the upper bound of the distribution and `v_m` being the lower bound. Each agent re-samples the threshold from the distribution at every decision step. (p.4)

### **Latent and interactive agents:**
Agents might not be able to interact with neighbours every `τ` seconds. For instance, an agent might be busy estimating the quality of a discovered option, or spatial/topological factors might prevent frequent interactions. Agents unable to interact are latent, as opposed to interactive ones (zie opnieuw figuur voor transities tussen deze 2 soorten). An agent becomes latent with probability `P_L`, and returns interactive with probability `P_I`. A fraction of `n_I = P_I/(P_I + P_L)` agents can be found in the interactive state. A fraction of `n_L = P_L/(P_I + P_L)` agents can be found in the latent state. The activity switch is possible for both committed and uncommitted agents, leading to a PFSM description with `2(n + 1)` states (zie figuur). Recruitment and cross-inhibition are available only to interactive agents, while discovery and abandonment are available also to latent agents. Given the microscopic description, it is possible to derive the correspondence between micro and macro parameters by dividing the macroscopic transition rates by `n_I` or `n_L` (zie artikel voor welke formules dit geldt). (p.5)

### **Metrics:**
Whenever time is required to gather sufficient information, decision-making gives rise to speed-accuracy tradeoffs.  In collective decision-making, a high coherence of the group is also important, as it can minimise the costs for conflicting choices by individuals. As maintaining coherence is a time-consuming process that requires to spread information widely within the group, speed-cohesion tradeoffs may also appear. (p.6)

Accuracy can be defined as the proportion of the group that is committed to the best option, or to any of the equal-best options. Cohesion measures the ability of the group to be committed to the same option, notwithstanding its quality. (p.6)

Resolution `R`: the ability to discriminate between different-quality options, and is related to the normalised quality difference between any two options `A` and `B`. `R = |V_A - V_B| / max(V_A,V_B)`.  By requiring a target resolution, the designer can focus on maximising accuracy only in those portions of the problem space that are above resolution, and just require that any solution is chosen below the given resolution threshold. (p.6)

Effectivity `E`: the ability of the group to take a decision within the maximum execution time `T`, measured as the fraction of runs that reach the quorum within the given time limit. Effectivity is related to the coherence of decision-making, as it measures the ability to take a decision (i.e., reach the predefined quorum) within the maximum allotted time, notwithstanding the quality of the chosen option. (p.6)

Success rate `S`: the fraction of effective runs resulting in a correct decision (the quorum is reached for the best option) when starting from a fully-uncommitted population. Exit probability in stochastic processes. (p.6)

Convergence time `C`: the average time required to reach the quorum computed over all effective runs. Exit time of stochastic processes. (p.6)

### **Multiagent simulations on fully-connected networks:**
At simulation start, each agent estimates the quality of all available options and on that basis computes its own transition probabilities. In the homogeneous case, these are computed in the same way for each agent according to the desired parameterisation. In the heterogeneous case, each agent draws a random threshold from the random distribution and computes the transition probabilities. The simulation proceeds in discrete time steps. At each time step, every agent updates its state following the PFSM. Interactive transitions depend on the interaction with a randomly selected partner, who shares its own commitment state and probabilities of recruitment and cross-inhibition. The populationdependent probabilities are estimated by randomly choosing a different agent as partner at each time step and checking its state: transitions are activated if the selected partner is committed to some option. The probability of recruitment and of cross-inhibition are received from the selected partner, otherwise they are null. In this way, the agent has complete information to update its commitment state. (p.12)