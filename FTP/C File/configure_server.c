#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    // Check if vsftpd is installed
    if (system("which vsftpd > /dev/null 2>&1") != 0) {
        printf("vsftpd is not installed. Installing...\n");
        system("sudo apt-get update");
        system("sudo apt-get install -y vsftpd");
    } else {
        printf("vsftpd is already installed.\n");
    }

    // Check if vsftpd.conf file exists and make changes if necessary
    char *config_file = "/etc/vsftpd.conf";
    FILE *file = fopen(config_file, "r");
    if (file != NULL) {
        fclose(file);

        // Uncomment lines if they are commented
        system("sudo sed -i '/^#anonymous_enable=/ s/^#//' /etc/vsftpd.conf");
        system("sudo sed -i '/^#ascii_upload_enable=/ s/^#//' /etc/vsftpd.conf");
        system("sudo sed -i '/^#ascii_download_enable=/ s/^#//' /etc/vsftpd.conf");

        // Make changes to configuration or add if not present
        if (system("grep -q '^anonymous_enable=' /etc/vsftpd.conf") == 0) {
            system("sudo sed -i '/^anonymous_enable=/ s/.*/anonymous_enable=NO/' /etc/vsftpd.conf");
        } else {
            system("echo 'anonymous_enable=NO' | sudo tee -a /etc/vsftpd.conf > /dev/null");
        }

        if (system("grep -q '^ascii_upload_enable=' /etc/vsftpd.conf") == 0) {
            system("sudo sed -i '/^ascii_upload_enable=/ s/.*/ascii_upload_enable=YES/' /etc/vsftpd.conf");
        } else {
            system("echo 'ascii_upload_enable=YES' | sudo tee -a /etc/vsftpd.conf > /dev/null");
        }

        if (system("grep -q '^ascii_download_enable=' /etc/vsftpd.conf") == 0) {
            system("sudo sed -i '/^ascii_download_enable=/ s/.*/ascii_download_enable=YES/' /etc/vsftpd.conf");
        } else {
            system("echo 'ascii_download_enable=YES' | sudo tee -a /etc/vsftpd.conf > /dev/null");
        }

        printf("Changes applied.\n");
    } else {
        printf("vsftpd configuration file not found at %s.\n", config_file);
    }

    // Restart vsftpd
    system("sudo systemctl restart vsftpd");
    system("sudo systemctl enable vsftpd");

    printf("vsftpd configuration and service restart complete.\n");

    return 0;
}
