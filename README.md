# swarm-robotics-thesis
Master's thesis on swarm robotics and collective decision making.

## Installation on WSL
Install Xming on Windows:
https://sourceforge.net/projects/xming

Open WSL and enable seeing GUI on Windows screen:
```bash
echo "export DISPLAY=:0" >> ~/.bashrc
source ~/.bashrc
```

Install ARGoS:
```bash
git clone https://github.com/WoutProvost/swarm-robotics-thesis
cd swarm-robotics-thesis
sudo dpkg -i argos3_simulator-*.deb
sudo apt --fix-broken install
```

Download and install examples:
```bash
cd ..
git clone https://github.com/ilpincy/argos3-examples
cd argos3-examples
mkdir build
cd build
cmake ..
make
cd ..
```

Start example:
```bash
argos3 -c experiments/diffusion_1.argos
```