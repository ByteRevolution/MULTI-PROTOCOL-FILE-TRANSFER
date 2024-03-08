#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void WriteInfo();

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
    int sr_no;
    char username[21];
    char ip[21];
};

int ssh() {
    struct userinfo user;

    FILE *fp=fopen("userinfo.bin","ab");
    if(fp == NULL)
    {
        fprintf(stderr,"Error opening file\n");
    }

    long int file_size = ftell(fp);

    int struct_size = sizeof(struct userinfo);

    static int currnt_sr_no ;
    currnt_sr_no= file_size/struct_size;

    int new_sr_no = currnt_sr_no + 1;

    user.sr_no = new_sr_no;

    printf("\n");
    printline(35);
    printf("Enter your username: ");
    fgets(user.username, sizeof(user.username), stdin);
    printf("Enter the IP address: ");
    fgets(user.ip, sizeof(user.ip), stdin);
    printline(35);

    // Remove newline characters from input
    user.username[strcspn(user.username, "\n")] = '\0';
    user.ip[strcspn(user.ip, "\n")] = '\0';
    
    fwrite(&user, sizeof(struct userinfo), 1, fp);
    fclose(fp);
   
    char command[200];
    snprintf(command, sizeof(command), "./ssh.sh %s %s", user.username, user.ip);
    system(command);

    return 0;
}

/*int ssh()
{
    system("systemctl restart sshd");
    printf("\n");
    // Path to your shell script
    char *scriptPath = "./ssh.sh";

    // Execute the shell script
    system(scriptPath);

    return 0;
}*/
