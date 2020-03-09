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
cd code
mkdir build
cd build
cmake ..
make
```

## Execution:
```bash
argos3 -c ../experiments/fire_evac.argos
```
