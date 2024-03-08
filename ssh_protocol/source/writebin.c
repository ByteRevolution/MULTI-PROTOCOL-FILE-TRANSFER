#include<stdio.h>
#include<stdlib.h>
#include <string.h>

void printline(int n);

struct userinfo
{
    int sr_no;
    char username[21];
    char ip[21];
};

void ReadInfo()
{
  struct userinfo user;
  FILE* Fptr;
  if ((Fptr = fopen("userinfo.bin", "rb")) == NULL)
  {
    printf("Error! opening file\n");

    exit(1);
  }

    printf("\n");
    printline(45);
    printf("%-10s %-20s %-20s\n","SR NO.","USERNAME","IP ADDRESS");
    printline(45);
   while(fread(&user, sizeof(struct userinfo), 1, Fptr)==1)
   {
    printf("%-10d %-20s %-20s\n",user.sr_no,user.username,user.ip);
    }
    printline(45);
  fclose(Fptr);
}
