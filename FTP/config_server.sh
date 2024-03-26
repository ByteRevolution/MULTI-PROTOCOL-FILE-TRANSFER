#!/bin/bash

# Check if vsftpd is installed
if ! command -v vsftpd &> /dev/null; then
    echo "vsftpd is not installed. Installing..."
    sudo apt-get update
    sudo apt-get install -y vsftpd
else
    echo "vsftpd is already installed."
fi

# Check if vsftpd.conf file exists and make changes if necessary
config_file="/etc/vsftpd.conf"

if [ -f "$config_file" ]; then
    # Uncomment lines if they are commented
    sudo sed -i '/^#anonymous_enable=/ s/^#//' "$config_file"
    sudo sed -i '/^#ascii_upload_enable=/ s/^#//' "$config_file"
    sudo sed -i '/^#ascii_download_enable=/ s/^#//' "$config_file"

    # Make changes to configuration or add if not present
    if grep -q "^anonymous_enable=" "$config_file"; then
        sudo sed -i '/^anonymous_enable=/ s/.*/anonymous_enable=NO/' "$config_file"
    else
        echo "anonymous_enable=NO" | sudo tee -a "$config_file" > /dev/null
    fi

    if grep -q "^ascii_upload_enable=" "$config_file"; then
        sudo sed -i '/^ascii_upload_enable=/ s/.*/ascii_upload_enable=YES/' "$config_file"
    else
        echo "ascii_upload_enable=YES" | sudo tee -a "$config_file" > /dev/null
    fi

    if grep -q "^ascii_download_enable=" "$config_file"; then
        sudo sed -i '/^ascii_download_enable=/ s/.*/ascii_download_enable=YES/' "$config_file"
    else
        echo "ascii_download_enable=YES" | sudo tee -a "$config_file" > /dev/null
    fi

    echo "Changes applied."
else
    echo "vsftpd configuration file not found at $config_file."
fi

# Restart vsftpd
sudo systemctl restart vsftpd
sudo systemctl enable vsftpd

echo "vsftpd configuration and service restart complete."
