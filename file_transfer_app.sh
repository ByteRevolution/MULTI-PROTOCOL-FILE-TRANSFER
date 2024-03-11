#!/bin/bash

# Function to set up NFS on the server (sender)
setup_nfs_server() {
    # Install NFS server
    sudo apt-get update
    sudo apt-get install -y nfs-kernel-server

    # Create a directory to share
    sudo mkdir -p /shared_folder
    sudo chmod -R 777 /shared_folder

    # Configure NFS exports
    echo "/shared_folder *(rw,sync,no_root_squash,no_subtree_check)" | sudo tee -a /etc/exports

    sudo exportfs -rv
# Restart NFS server
    sudo systemctl restart nfs-kernel-server

    echo "NFS server setup complete."
}

# Function to set up NFS on the client (receiver)
setup_nfs_client() {
    # Install NFS client
    sudo apt-get update
    sudo apt-get install -y nfs-common
    sudo mkdir -p /mnt/shared_folder
}

# Function to transfer files from source to shared folder on the server (sender)
transfer_files_to_shared_folder() {
    if [ $# -lt 1 ]; then
        echo "Usage: transfer_files_to_shared_folder <SOURCE_PATH>"
        exit 1
    fi

    cp -r $1 /shared_folder/
    echo "Files copied to shared folder on the server (sender)."
}

# Function to mount shared folder from the server (sender) on the client (receiver)
mount_shared_folder_on_client() {
    if [ $# -lt 1 ]; then
        echo "Usage: mount_shared_folder_on_client <SERVER_IP>"
        exit 1
    fi

    # Mount the NFS share from the server (sender) to /mnt/shared_folder on the client (receiver)
    sudo mount -t nfs $1:/shared_folder /mnt/shared_folder

    echo "NFS client setup complete. The shared folder is mounted at /mnt/shared_folder."
}

# Main flow
if [ "$1" == "server" ]; then
    setup_nfs_server
    transfer_files_to_shared_folder $2
elif [ "$1" == "client" ]; then
    if [ $# -lt 2 ]; then
        echo "Usage: $0 client <SERVER_IP>"
        exit 1
    fi

    setup_nfs_client
    mount_shared_folder_on_client $2
else
    echo "Usage: $0 {server|client}"
    exit 1
fi
