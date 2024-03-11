#include <stdio.h>
#include <stdlib.h>

void display_menu() {
    printf("File Transfer Application Menu\n");
    printf("1. Sender\n");
    printf("2. Receiver\n");
    printf("3. Exit\n");
}

int main() {
    int choice;
    char source_path[100];
    char server_ip[20];

    while (1) {
        display_menu();
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter the file path for the sender: ");
                scanf("%s", source_path);
                char sender_command[200];
                snprintf(sender_command, sizeof(sender_command), "bash file_transfer_app.sh server %s", source_path);
                system(sender_command);
                break;

            case 2:
                printf("Enter the IP address of the sender: ");
                scanf("%s", server_ip);
                char receiver_command[200];
                snprintf(receiver_command, sizeof(receiver_command), "bash file_transfer_app.sh client %s", server_ip);
                system(receiver_command);
                break;

            case 3:
                printf("Exiting the File Transfer Application. Goodbye!\n");
                return 0;

            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}

