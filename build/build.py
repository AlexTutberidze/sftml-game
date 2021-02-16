#!/usr/bin/env python3

import os
import platform

os.system("sudo apt-get update")

os.system("[ -f /usr/bin/g++ ] && echo g++ is already installed || sudo apt install -y g++")

os.system("sudo apt-get install python3-pip")

os.system("pip3 install pip-custom-platform")


os.system("g++ ../src/server.cpp -o ../bin/server.exe -lsfml-system -lsfml-network -pthread")
os.system("g++ ../src/client.cpp ../src/player.cpp -o ../bin/client.exe -lsfml-graphics -lsfml-window -lsfml-system -lsfml-network -pthread")

os.system('clear' if platform.system() == 'Linux' else 'Windows' 'cls') 

# os.system("./../bin/server.exe")
# os.system("./../bin/client.exe")
