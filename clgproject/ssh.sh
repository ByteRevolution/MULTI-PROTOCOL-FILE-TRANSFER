#!/bin/bash

echo -n "Enter Usrename: "
read USERNAME
echo -n "Enter IP: "
read IP

# SSH command to execute on the remote server
ssh "$USERNAME@$IP" -p 22
