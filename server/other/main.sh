#!/bin/bash
echo you opt for the samba sharing server side configuration

echo checking dependencies...
bash package.sh

echo dependencies check complete...
echo checking firewall status...

# Function to display menu
display_menu() {
    echo "Samba Configuration Menu"
    echo "1. Configure an Existing Folder"
    echo "2. Create and Configure a New Folder"
    echo "3. Restart Samba Service"
    echo "4. Exit"
}

# Function to configure an existing folder
configure_existing_folder() {
    read -p "Enter the folder name to configure: " folder_name
    if [ -z "$folder_name" ]; then
        echo "Folder name cannot be empty."
        return
    fi
    
    # Check if folder exists
    if [ ! -d "$folder_name" ]; then
        echo "Folder '$folder_name' does not exist."
        return
    fi
    
    # Add configuration to smb.conf
    echo "[$folder_name]" >> /etc/samba/smb.conf
    echo "   path = $folder_name" >> /etc/samba/smb.conf
    echo "   browseable = yes" >> /etc/samba/smb.conf
    echo "   writable = yes" >> /etc/samba/smb.conf
    
    echo "Samba configuration for '$folder_name' added successfully."
}

# Function to create and configure a new folder
create_and_configure_folder() {
    read -p "Enter the folder name to create and configure: " folder_name
    if [ -z "$folder_name" ]; then
        echo "Folder name cannot be empty."
        return
    fi
    
    mkdir -p "$folder_name"
    
    # Add configuration to smb.conf
     bash sudo echo "getting root access"
     echo "[$folder_name]" >> /etc/samba/smb.conf 
     echo "   path = $PWD/$folder_name" >> /etc/samba/smb.conf
     echo "   browseable = yes" >> /etc/samba/smb.conf
     echo "   writable = yes" >> /etc/samba/smb.conf
    echo "Folder '$folder_name' created and configured for sharing."
}

# Function to restart Samba service
restart_samba_service() {
    echo "Restarting Samba service..."
    systemctl restart smbd
    echo "Samba service restarted."
}

# Main function
main() {
    while true; do
        display_menu
        read -p "Enter your choice: " choice
        case $choice in
            1)
                configure_existing_folder
                ;;
            2)
                create_and_configure_folder
                ;;
            3)
                restart_samba_service
                ;;
            4)
                echo "Exiting program."
                exit 0
                ;;
            *)
                echo "Invalid choice. Please enter a valid option."
                ;;
        esac
    done
}

# Call the main function
main


