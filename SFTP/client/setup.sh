#!/bin/bash

# Check if sshpass is installed
if ! command -v sshpass &> /dev/null
then
    echo "sshpass is not installed. Installing..."
    # Install sshpass
    sudo apt-get install -y sshpass
else
    echo "sshpass is installed."
fi

# Check if ssh is installed
if ! command -v ssh &> /dev/null
then
    echo "ssh is not installed. Installing..."
    # Install ssh
    sudo apt-get install -y ssh
else
    echo "ssh is installed."
fi
