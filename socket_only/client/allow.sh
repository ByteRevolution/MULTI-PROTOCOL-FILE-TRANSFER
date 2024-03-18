#!/bin/bash

# Check if argument is provided
if [ $# -ne 1 ]; then
    echo "Usage: $0 <server_ip>"
    exit 1
fi

# Add server IP to UFW allow list
sudo ufw allow from $1
sudo ufw reload
