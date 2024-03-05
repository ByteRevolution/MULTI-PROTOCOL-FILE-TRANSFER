#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>

#define SIZE 1024


void write_file(int sockfd)
{
    int n;
    FILE *fp;
    char *filename = "file.jpg"; // Change filename as needed
    char buffer[SIZE];

    fp = fopen(filename, "wb"); // Open file in binary write mode
    if (fp == NULL)
    {
        perror("[-]Error in creating file.");
        exit(1);
    }
    while (1)
    {
        n = recv(sockfd, buffer, SIZE, 0);
        if (n <= 0)
        {
            break;
        }
        fwrite(buffer, 1, n, fp); // Write received binary data directly to file
        bzero(buffer, SIZE);
    }
    fclose(fp); // Close file after writing
}



int main ()
{
    char *ip = "192.168.207.30";
    int port = 8080;
    int e;

    int sockfd, new_sock;
    struct sockaddr_in server_addr, new_addr;
    socklen_t addr_size;
    char buffer[SIZE];

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

     e = bind(sockfd,(struct sockaddr*)&server_addr, sizeof(server_addr));
     if(e<0)
     {
         perror("[-]Error in Binding");
         exit(1);
     }
     printf("[+]Binding Successfull.\n");

     e = listen(sockfd, 10);
     if(e==0)
     {
         printf("[+]Listening...\n");
     }
     else 
     {
         perror("[-]Error in Binding");
         exit(1);
     }
     addr_size = sizeof(new_addr);
     new_sock = accept(sockfd,(struct sockaddr*)&new_addr, &addr_size);

     write_file(new_sock);
     printf("[+]Data written in the file \n");
}
