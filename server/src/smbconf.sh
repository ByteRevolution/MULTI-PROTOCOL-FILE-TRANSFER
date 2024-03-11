#!/bin/bash

echo "Opening the smb.conf file for writing"
smb_conf="/etc/samba/smb.conf"

if ! sudo test -w "$smb_conf"; then
    echo "Failed to open smb.conf for writing."
    exit 1
fi

folder_name="$1"
if [ -z "$folder_name" ]; then
    echo "Folder name not provided."
    exit 1
fi

# Get the current working directory
current_dir=$(pwd)

# Write configuration to smb.conf
{
    echo "[$folder_name]"
    echo "   path = $current_dir/$folder_name"
    echo "   browseable = yes"
    echo "   writable = yes"
    echo "   valid users = ByteRevolution"
} | sudo tee -a "$smb_conf" > /dev/null

echo "Folder '$folder_name' created and configured for sharing."
