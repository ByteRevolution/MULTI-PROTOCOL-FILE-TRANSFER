#!/bin/bash

check_package() {
    if dpkg -s "$1" &> /dev/null; then
        echo "$1 is already installed."
        return 0
    else
        echo "$1 is not installed."
        return 1
    fi
}

install_package() {
    sudo apt-get install -y "$1"
    if [ $? -eq 0 ]; then
        echo "$1 has been installed successfully."
    else
        echo "Failed to install $1."
    fi
}

package_name="samba"

check_package "$package_name"
if [ $? -ne 0 ]; then
    install_package "$package_name"
fi

