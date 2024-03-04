#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>

#define SIZE 1024

void send_file(FILE *fp, int sockfd)
{
    char data[SIZE];
    size_t bytes_read;

    while ((bytes_read = fread(data, 1, SIZE, fp)) > 0)
    {
        if (send(sockfd, data, bytes_read, 0) == -1)
        {
            perror("[-] Error in sending data");
            exit(1);
        }
    }

    if (ferror(fp))
    {
        perror("[-] Error reading file");
        exit(1);
    }
}

int main()
{
    char *ip = "192.168.207.30";
    int port = 8080;
    int e;

    int sockfd;
    struct sockaddr_in server_addr;
    FILE *fp;
    char *filename = "7seg.jpg";
     sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd<0)
    {
        perror("[-]Error in socket");
        exit(1);
    }
     printf("[+]Server socket created. \n");

     server_addr.sin_family = AF_INET;
     server_addr.sin_port = port;
     server_addr.sin_addr.s_addr = inet_addr(ip);

     e = connect(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr));
     if(e == -1)
     {
         perror("[-]Error in Connecting");
         exit(1);
     }
     printf("[+]Connected to server.\n");
     fp = fopen(filename, "rb");
     if(fp == NULL)
     {
         perror("[-]Error in reading file.");
         exit(1);
     }
     send_file(fp,sockfd);
     printf("[+] File data send successfully. \n");
     close(sockfd);
     printf("[+]Disconnected from the server. \n");
     return 0;

}
