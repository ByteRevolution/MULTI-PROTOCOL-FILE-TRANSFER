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

install_package() 
{
	echo Enter correct superuser password :
    sudo apt-get install -y "$1"
    if [ $? -eq 0 ]; then
        echo "$1 has been installed successfully."
    else
        echo "Failed to install $1."
    fi
}
echo Dependency check for the samba sharing...
package_name=("samba"" ufw")
for pkg in ${package_name[@]};do
check_package "$pkg"
if [ $? -ne 0 ]; then
    install_package "$pkg"
fi
done

