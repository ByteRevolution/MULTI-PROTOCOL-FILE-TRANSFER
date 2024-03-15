#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    // Check if Telnet is installed
    FILE *telnet_check = popen("dpkg -s telnet | grep Status", "r");
    char telnet_status[50];
    fgets(telnet_status, sizeof(telnet_status), telnet_check);

    // If Telnet is not installed, install it
    if (strstr(telnet_status, "install ok installed") == NULL) {
        printf("Telnet is not installed. Attempting to install...\n");
        int status = system("sudo apt-get install telnet");

        if (status == 0) {
            printf("Telnet has been successfully installed.\n");
        } else {
            printf("Failed to install Telnet.\n");
            return 1; // Exit with error
        }
    } else {
        printf("Telnet is already installed.\n");
    }

    // Ask user for the IP address to connect with
    char ip_address[20];
    printf("Enter the IP address to connect with: ");
    scanf("%s", ip_address);

    // Construct the Telnet command
    char telnet_command[50];
    snprintf(telnet_command, sizeof(telnet_command), "telnet %s", ip_address);

    // Connect via Telnet
    printf("Connecting to %s...\n", ip_address);
    int connection_status = system(telnet_command);

    if (connection_status != 0) {
        printf("Failed to connect to %s via Telnet.\n", ip_address);
        return 1; // Exit with error
    }

    return 0;
}
