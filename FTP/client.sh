#!/bin/bash

# Check if ftp client is installed
if ! command -v ftp &> /dev/null; then
    echo "ftp client is not installed. Installing..."
    sudo apt-get update
    sudo apt-get install -y ftp
else
    echo "ftp client is already installed."
fi

# Ask for FTP server IP
read -p "Enter FTP server IP address: " ftp_server_ip

# Ask for username and password if needed
read -p "Enter username (press Enter if not needed): " username
read -s -p "Enter password (press Enter if not needed): " password

# Connect to FTP server
if [[ -n "$username" ]]; then
    echo "Connecting to FTP server $ftp_server_ip with username $username..."
    ftp -n $ftp_server_ip <<END_SCRIPT
    quote USER $username
    quote PASS $password
    quit
END_SCRIPT
else
    echo "Connecting to FTP server $ftp_server_ip..."
    ftp -n $ftp_server_ip <<END_SCRIPT
    quit
END_SCRIPT
fi

echo "FTP connection completed."
