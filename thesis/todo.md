# TODO:
- Random walk parameter: 60s
- Reaction strategy percentage threshold: 100%, 60%
- Multiple fires

# Multiple fires
- Remember what you mentioned: our brain applies some kind of heuristic to determine which fire should be prioritized.
- That heuristic is: which of the fire sources is CLOSEST to ANY of the exits?
==> Instead of basing the quality on the furthest distance to the exit, base it on the closest distance to the exit.
==> Instead of multiplying the temperature by the distance to get the quality, divide the temperature by the distance.
==> Old method:
	1) Red: 11.1m
	   Blue: 9.3m
	   Choose exit with distance furthest away from current position for quality comparison (Red)
	   Choose exit with distance furthest away from current position to update preferred exit (Red)
	2) Red: 6.2m
	   Blue: 8.6m
	   Choose exit with distance furthest away from current position for quality comparison (Blue)
	   Choose exit with distance furthest away from current position to update preferred exit (Blue)
	3) Fire 1 wins over fire 2, because it has higher multiplied quality
	   255° * 11.1m = 2830.5 > 255° * 8.6 = 2193
==> New method:
	1) Red: 11.1m
	   Blue: 9.3m
	   Choose exit with distance closest to current position for quality comparison (Blue)
	   Choose exit with distance furthest away from current position to update preferred exit (Red)
	2) Red: 6.2m
	   Blue: 8.6m
	   Choose exit with distance closest to current position for quality comparison (Red)
	   Choose exit with distance furthest away from current position to update preferred exit (Blue)
	3) Fire 2 wins over fire 1, because it has higher fractional quality
	   255° / 9.3m = 27.42 < 255° / 6.2 = 41.13
- Due to the change, results using the previous algorithm aren't perfectly up to date anymore, but the results are still valid for that old algorithm, which is described in the paper.
- New param multiple_fire_sources_support_version.

- Use timesteps in thesis, not seconds! Mention the amount of timesteps per second.
- Random walk parameter doesn't go too high, since otherwise it will enable grouping again, which is what we tried to cancel out.
- Mail plot results to Y. Khaluf
- 41.13 is used for selecting the fire => most critical fire.
- Afer this, we compute the furthest exit from that fire.
- Don't mention old and new, for single fire we don't care about criticality.
- Since we know as a designer that we only have a single fire...
- One is an extension of the other.
- Don't use version 1 and 2, because 2 is more general, we disabled fire criticality.
- Phases are implicitely already combined
- Group bar plot for single fire and multiple fire
- Those decision strategies because they are mostly used in decision making.
- Those reaction strategies, because this is the thesis novelty.
- Plots for exit probabilities + plot for correct response (not only decision), that the grippers are following the decision of the sensor robots + how long it takes the grippers to react + speed of conversion.
- Whatever you study for sensor robots, do this for gripper robots as well.
- Focus on accuracy (exit probability) + speed of decision (how long it takes the robots to decide on the exit), do this for both robot types.