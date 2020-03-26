# swarm-robotics-thesis
Master's thesis on swarm robotics and collective decision making.

## ARGoS installation:
```bash
git clone https://github.com/WoutProvost/swarm-robotics-thesis
cd swarm-robotics-thesis
sudo dpkg -i download/argos3_simulator-*.deb
sudo apt --fix-broken install
```

## Compilation:
```bash
mkdir frames
mkdir build
cd build
cmake ..
make
```

## Execution:
```bash
argos3 -c ../experiments/fire_evacuation.argos
```

## Configuration:
Controller **general** params:
* `leds_color`:
  * The gate gripping footbot defaults to `black`.
  * The temperature sensing footbot defaults to `white`.

Controller **movement** params:
* `max_velocity`: Defaults to `10.0`.
* `max_heading_angle_for_no_turn`: Defaults to `10.0`.
* `min_heading_angle_for_hard_turn`: Defaults to `90.0`.

Controller **collision avoidance** params:
* `max_angle_between_heading_and_obstacle`: Defaults to `5.0`.
* `max_obstacle_proximity`: Defaults to `0.1`.

Loop functions **heatmap** params:
* `tiles_per_meter`: Defaults to `10`.
* `max_temperature`:
  * Maximum of `255`, since the grayscale color range is [0, 255];
  * Defaults to `255`.
* `show_temperature`: Defaults to `true`.
* `debug_mode`:
  * Mode `gradient` is useful to show the whole temperature range in terms of steps.
  * Mode `resolution` is useful to show how large the tiles are compared to the robots.
  * Defaults to `none`.
* `debug_use_colors`:
  * The simulation only works with grayscale, so make sure to disable color after debugging.
  * Defaults to `false`.

Loop functions **fire** params:
* `mode`:
  * Currently only 1 mode is supported.
  * Defaults to `circle`.
* `circle_radius`: Defaults to `3.0`.
* `is_dynamic`: Defaults to `false`.
* `dynamic_interval_ticks`: Defaults to `50`.
* `dynamic_temperature_increase`: Defaults to `5`.

Loop functions **plot** params:
* `log_data`: Defaults to `false`.
* `show_in_realtime`: Defaults to `false`.
* `realtime_initial_x_axis_max_value`: Defaults to `60`.