
#include <sys/stat.h>

#include "../../include/comman.h"
#include "colors_effects.h"

#define MAX_PATH_LENGTH 100

// Function to display menu
void display_menu() {
    printf(YELLOW "Samba Configuration Menu\n");
    printf("1. Configure an Existing Folder\n");
    printf("2. Create and Configure a New Folder\n");
    printf("3. Restart Samba Service\n");
    printf("4. Exit\n" RESET);
}

// Function to configure an existing folder
void configure_existing_folder() {
    char folder_name[MAX_PATH_LENGTH];
    printf("Please provide the absolute path: ");
    fgets(folder_name, sizeof(folder_name), stdin);
    folder_name[strcspn(folder_name, "\n")] = '\0'; // remove trailing newline
    
    if (strlen(folder_name) == 0) {
        printf("Folder name cannot be empty.\n");
        return;
    }
    
    // Check if folder exists
    struct stat st;
    if (stat(folder_name, &st) != 0 || !S_ISDIR(st.st_mode)) {
        printf("Folder '%s' does not exist.\n", folder_name);
        return;
    }

    // Check if Samba user exists
    if (system("id -u ByteRevolution >/dev/null 2>&1") != 0) {
        // Create Samba user
        if (system("sudo useradd ByteRevolution -m -s /sbin/nologin") != 0) {
            printf("Failed to create user 'ByteRevolution'.\n");
            return;
        }
        // Set password for Samba user
        if (system("(echo -e 'revolve\nrevolve' | sudo smbpasswd -a ByteRevolution) && sudo smbpasswd -e ByteRevolution") != 0) {
            printf("Failed to set password for 'ByteRevolution'.\n");
            return;
        }
        printf("Password set for user 'ByteRevolution'.\n");
        printf("User 'ByteRevolution' created.\n");
    } else {
        printf("User 'ByteRevolution' already exists.\n");
    }
    
    // Add configuration to smb.conf
    FILE *smb_conf = fopen("/etc/samba/smb.conf", "a");
    if (smb_conf == NULL) {
        printf("Failed to open smb.conf for writing.\n");
        return;
    }
    
    fprintf(smb_conf, "\n[%s]\n", folder_name);
    fprintf(smb_conf, "   path = %s\n", folder_name);
    fprintf(smb_conf, "   browseable = yes\n");
    fprintf(smb_conf, "   writable = yes\n");
    fprintf(smb_conf, "   valid users = ByteRevolution\n");
    
    fclose(smb_conf);
    
    printf("Samba configuration for '%s' added successfully.\n", folder_name);
}

// Function to create and configure a new folder
void create_and_configure_folder() {
    char folder_name[MAX_PATH_LENGTH];
    printf("Enter the folder name to create and configure: ");
    fgets(folder_name, sizeof(folder_name), stdin);
    folder_name[strcspn(folder_name, "\n")] = '\0'; // remove trailing newline

    if (strlen(folder_name) == 0) {
        printf("Folder name cannot be empty.\n");
        return;
    }
    
    // Check if folder already exists
    struct stat st;
    if (stat(folder_name, &st) == 0 && S_ISDIR(st.st_mode)) {
        printf("Folder '%s' already exists.\n", folder_name);
        return;
    }

    // Create folder
    if (mkdir(folder_name, 0777) != 0) {
        printf("Failed to create folder '%s'.\n", folder_name);
        return;
    }
    
    // Add configuration to smb.conf
    FILE *smb_conf = fopen("/etc/samba/smb.conf", "a");
    if (smb_conf == NULL) {
        printf("Failed to open smb.conf for writing.\n");
        return;
    }
    
    fprintf(smb_conf, "\n[%s]\n", folder_name);
    fprintf(smb_conf, "   path = %s\n", folder_name);
    fprintf(smb_conf, "   browseable = yes\n");
    fprintf(smb_conf, "   writable = yes\n");
    fprintf(smb_conf, "   valid users = ByteRevolution\n");
    
    fclose(smb_conf);
    
    printf("Folder '%s' created and configured for sharing.\n", folder_name);
}

// Function to restart Samba service
void restart_samba_service() {
    printf("Restarting Samba service...\n");
    system("sudo systemctl restart smbd");
    printf("Samba service restarted.\n");
}

// Main function
int main() {
    system("bash ./server/src/package.sh");

    int choice;
    while (1) {
        display_menu();
        printf(BOLD "Enter your choice: " RESET);
        scanf("%d", &choice);
        getchar(); // consume newline
        
        switch (choice) {
            case 1:
                configure_existing_folder();
                break;
            case 2:
                create_and_configure_folder();
                break;
            case 3:
                restart_samba_service();
                break;
            case 4:
                printf("Exiting program.\n");
                return 0;
            default:
                printf("Invalid choice. Please enter a valid option.\n");
                break;
        }
    }
    return 0;
}
