#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*int main() {
    system("systemctl restart sshd");
    char username[20];
    char ip[20];
    
    printf("Enter your username: ");
    fgets(username, sizeof(username), stdin);
    printf("Enter the IP address: ");
    fgets(ip, sizeof(ip), stdin);

    // Remove newline characters from input
    username[strcspn(username, "\n")] = '\0';
    ip[strcspn(ip, "\n")] = '\0';

    char command[200];
    snprintf(command, sizeof(command), "./ssh.sh %s %s", username, ip);
    system(command);

    return 0;
}*/

int main()
{
    // Path to your shell script
    char *scriptPath = "./ssh.sh";

    // Execute the shell script
    int result = system(scriptPath);

    return 0;
}
