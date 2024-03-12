#include<stdio.h> 
#include<string.h> 
#include<stdlib.h> 

void printline(int n)
{
    for(int i=0;i<=n;i++)
    {
        printf("=");
    }
    printf("\n");
}


struct userinfo
{
    char username[21];
    char ip[21];
    char srcpath[51];
    char destpath[51];
};

int main() {

    struct userinfo user;

    printline(60);
    printf("Enter source path: ");
    fgets(user.srcpath, sizeof(user.srcpath), stdin);
    
    printf("Enter your username: ");
    fgets(user.username, sizeof(user.username), stdin);

    printf("Enter the IP address: ");
    fgets(user.ip, sizeof(user.ip), stdin);

    printf("Enter destination path: ");
    fgets(user.destpath, sizeof(user.destpath), stdin);
    printline(60);
    
    // Remove newline characters from input
    user.srcpath[strcspn(user.srcpath, "\n")] = '\0';
    user.username[strcspn(user.username, "\n")] = '\0';
    user.ip[strcspn(user.ip, "\n")] = '\0';
    user.destpath[strcspn(user.destpath, "\n")] = '\0';
    
    char command[200];
    snprintf(command, sizeof(command), "./scp.sh %s %s %s %s",user.srcpath, user.username, user.ip, user.destpath);
    system(command);

    return 0;
}
