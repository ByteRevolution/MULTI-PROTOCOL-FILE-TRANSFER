#!/bin/bash

# Now you can use $USERNAME and $IP in your script
# For example:
echo "Connecting to $1@$2"

# SSH command to execute on the remote server
ssh "$1@$2" -p 22
