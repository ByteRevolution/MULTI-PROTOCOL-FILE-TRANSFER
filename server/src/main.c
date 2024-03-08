#include "comman.h"
#include "colors_effects.h"
// Function to display menu
void display_menu() {
    printf(YELLOW);
    printf("Samba Configuration Menu\n");
    printf("1\\ Configure an Existing Folder\n");
    printf("2/ Create and Configure a New Folder\n");
    printf("3\\ Restart Samba Service\n");
    printf("4/ Exit\n");
    printf(RESET);
}

// Function to configure an existing folder
void configure_existing_folder() {
    char folder_name[100];
    printf("Enter the folder name to configure: ");
    fgets(folder_name, sizeof(folder_name), stdin);
    folder_name[strcspn(folder_name, "\n")] = 0; // remove trailing newline
    
    if (strlen(folder_name) == 0) {
        printf("Folder name cannot be empty.\n");
        return;
    }
    
    // Check if folder exists
    if (system(NULL)) {
        if (system("test -d \"$folder_name\"") != 0) {
            printf("Folder '%s' does not exist.\n", folder_name);
            return;
        }
    } else {
        printf("System command not available.\n");
        return;
    }
    
    // Add configuration to smb.conf
    FILE *smb_conf = fopen("/etc/samba/smb.conf", "a");
    if (smb_conf == NULL) {
        printf("Failed to open smb.conf for writing.\n");       
        return;
    }
    
    fprintf(smb_conf, "[%s]\n", folder_name);
    fprintf(smb_conf, "   path = %s\n", folder_name);
    fprintf(smb_conf, "   browseable = yes\n");
    fprintf(smb_conf, "   writable = yes\n");
    
    fclose(smb_conf);
    
    printf("Samba configuration for '%s' added successfully.\n", folder_name);
}

// Function to create and configure a new folder
void create_and_configure_folder() {
    char folder_name[100];
    printf("Enter the folder name to create and configure: ");
    fgets(folder_name, sizeof(folder_name), stdin);
    folder_name[strcspn(folder_name, "\n")] = 0; // remove trailing newline
    
    if (strlen(folder_name) == 0) {
        printf("Folder name cannot be empty.\n");
        return;
    }
    
    // Create folder
    if (system(NULL)) {
        if (system("mkdir -p \"$folder_name\"") != 0) {
            printf("Failed to create folder '%s'.\n", folder_name);
            return;
        }
    } else {
        printf("System command not available.\n");
        return;
    }
    
    // Add configuration to smb.conf
    FILE *smb_conf = fopen("/etc/samba/smb.conf", "a");
    if (smb_conf == NULL) {
        printf("Failed to open smb.conf for writing.\n");
        return;
    }
    
    fprintf(smb_conf, "[%s]\n", folder_name);
    fprintf(smb_conf, "   path = %s/%s\n", getenv("PWD"), folder_name);
    fprintf(smb_conf, "   browseable = yes\n");
    fprintf(smb_conf, "   writable = yes\n");
    
    fclose(smb_conf);
    
    printf("Folder '%s' created and configured for sharing.\n", folder_name);
}

// Function to restart Samba service
void restart_samba_service() {
    printf("Restarting Samba service...\n");
    system("systemctl restart smbd");
    printf("Samba service restarted.\n");
}

// Main function
int main() {
    printf(RED);
    system("bash ./server/src/package.sh");
    printf(RESET);
    int choice;
    while (1) {
        display_menu();
        PRINT_BOLD("enter your choice :");
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

