#!/bin/bash

# Extract the NAME of the OS and store it in a variable
OS_NAME=$(grep -oP '^NAME="\K[^"]+' /etc/os-release)

# Use an if/else statement to check the OS_NAME variable
if [ "$OS_NAME" == "Ubuntu" ]; then
    # 1. Update your package list
    sudo apt update

    # 2. Upgrade your package list
    sudo apt upgrade -y

    # 3. Install glog and other required libraries
    sudo apt install -y libgoogle-glog-dev libgflags-dev libgtest-dev

    # 4. (Optional) If you have issues, ensure build essentials are present
    sudo apt install build-essential cmake -y    
else
    echo "This is not an Ubuntu / Debian OS."
    # Place commands for other systems here
fi
