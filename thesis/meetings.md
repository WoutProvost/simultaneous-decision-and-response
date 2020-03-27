# Tuesday 24-03-2020
- 

# Tuesday 17-03-2020
- No meeting

# Thursday 12-03-2020
- No meeting

# Thursday 5-03-2020
- No meeting

# Thursday 27-02-2020
- Implement the static scenario (see picture from whiteboard)
- Heatmap + ground sensors (bottom sensors with gradient)

# Thursday 13-02-2020
- No meeting

# Thursday 20-02-2020
- No meeting

# Friday 7-02-2020
- Think of a scenario to implement
- Experiment with ARGoS
- Search for additional articles


- UGent GitHub doormailen naar Y. Khaluf
- UGent cluster
- phd student email to get acces to cluster

- static 2 or 3 fires, before dynamic
- compose opinion of 2 fields (temperature from position tile, transition from white tile to grayer tile they sense distance to gates)
- temperature of tile + which gate to use
- use votings trategy from papers (majority rule, weighted voter model, ...)
- at least 2 voting mechanisms to compare
- talk with neighbours, take average of neighbours, when to replace my data with neighbouring data
- bots with highest temperature are not always reliable
- neighbours (0.1, 0.2, 0.1) you can get direction of the fire, this data can be used to update decision about the gate you want to use

- gripper will hear those messages (gate A, gate B, ...)
- avoid cases where grippers start taking decision too early, but at the same time you don't want them to wait too long (time vs accuracy)
- quorum sensing in papers

- compute angle to each neighbour to compute fire spread (computed locally)
- you can compute the vector to the fire and use it in combination with the light from the gates (vectorToLight)
- flocking (vector of motion => gradient vector of fire)
- vector to red light
- vector to blue light
- if the fire is spreading to the direction of the blue gate, you pick the red gate
- this computation is only needed when the distance computation doesn't work 

- no noise for the moment
- velocity only important with dynamic scenario (how fast the fire spreads)
- RaB 1 or 1.3 meter (probably use different ranges later)

- perhaps 1 tile per robot width