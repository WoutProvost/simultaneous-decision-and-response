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