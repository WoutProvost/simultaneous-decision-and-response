# swarm-robotics-thesis
Master's thesis on swarm robotics and collective decision making.

## WSL Configuration
Install Xming on Windows:
https://sourceforge.net/projects/xming

Open WSL and enable seeing GUI on Windows screen:
```bash
echo "export DISPLAY=:0" >> ~/.bashrc
source ~/.bashrc
```

## ARGoS installation:
```bash
git clone https://github.com/WoutProvost/swarm-robotics-thesis
cd swarm-robotics-thesis
sudo dpkg -i argos3_simulator-*.deb
sudo apt --fix-broken install
```

## Compilation:
```bash
cd code
mkdir build
cd build
cmake ..
make
cd ..
```

## Execution:
```bash
argos3 -c experiments/fire_evac.argos
```