#!/bin/bash

usage() {
    echo "Usage: $0 [options] <filename>"
    echo "Options:"
    echo "  -h, --help             Display this help message"
    echo "  -d <path>, --destination <path>"
    echo "                         Specify the destination path on the server"
    echo "Arguments:"
    echo "  filename               Path to the file to transfer"
}

# Default destination path
destination="/home/jigar/SFTP/files/"

# Parse command-line options
while [[ "$1" =~ ^- ]]; do
    case $1 in
        -h | --help)
            usage
            exit 0
            ;;
        -d | --destination)
            shift
            destination="$1"
            ;;
        *)
            echo "Error: Invalid option: $1"
            usage
            exit 1
            ;;
    esac
    shift
done

# Check if filename argument is provided
if [ $# -ne 1 ]; then
    echo "Error: Invalid number of arguments."
    usage
    exit 1
fi

# Assign filename from command-line argument
filename="$1"

# Prompt for server hostname, IP address, and password
read -p "Enter the server hostname: " server_hostname
read -p "Enter the server IP address: " server_ip
read -s -p "Enter the server password: " server_password
echo ""

# Check if sshpass is installed
if ! command -v sshpass &> /dev/null; then
    echo "Installing sshpass..."
    sudo apt-get update
    sudo apt-get install -y sshpass
fi

# Transfer file from client to server
sshpass -p "$server_password" sftp -o StrictHostKeyChecking=no "$server_hostname"@"$server_ip" <<EOF
put "$filename" "$destination"
EOF

echo "File transfer complete."
