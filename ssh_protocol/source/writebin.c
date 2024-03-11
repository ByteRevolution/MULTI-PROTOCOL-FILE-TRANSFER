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

void update_entry(void)
{
    struct userinfo temp_data;

    int sr_no_to_update;

    printf("\n");
    printline(63);
    printf("Please enter the sr number of user you want to edit data of :");
    scanf("%d", &sr_no_to_update);
    getchar();

    FILE *user_file = fopen("userinfo.bin","rb+");
    if(user_file == NULL)
    {
    fprintf(stderr,"Error opening file\n");
    }

    while(fread(&temp_data,sizeof(struct userinfo),1,user_file) == 1)
    {
    if(sr_no_to_update == temp_data.sr_no)
    {
        printf("Please enter the new IP Address :");
            scanf("%21[^\n]", temp_data.ip);
            getchar();
            printline(63);

        fseek(user_file,-sizeof(struct userinfo),SEEK_CUR);
            fwrite(&temp_data,sizeof(struct userinfo),1,user_file);
        break;
    }
    else
    {
        printf("no entry found");
        break;
    }
    }

    fclose(user_file);
}

int RemoveInfo() {
    int sr_no_to_remove;

    printf("\n");
    printline(30);
    printf("Enter your sr_no: \n");
    scanf("%d",&sr_no_to_remove);
    printline(30);

    FILE* input_file = fopen("userinfo.bin", "rb");
    FILE* temp_file = fopen("updated.bin", "wb");

    if (input_file == NULL || temp_file == NULL) {
        printf("Error opening files.\n");
        return 1;
    }
    
    int new_sr_no = 1;
    int found = 0;
    struct userinfo record;
    while (fread(&record, sizeof(struct userinfo), 1, input_file) == 1) {
        
        if (record.sr_no == sr_no_to_remove) {
            found = 1;
            printf("Record with serial number %d removed successfully.\n\n", sr_no_to_remove);
        }
        else {
            record.sr_no = new_sr_no;
            fwrite(&record, sizeof(struct userinfo), 1, temp_file);
            new_sr_no++;
        }

    }

        if(!found)
        {
            printf("No data available with this serial number !!\n");
        }

    // Close both files
    fclose(input_file);
    fclose(temp_file);

    // Remove the original file and rename the temporary file
    remove("userinfo.bin");
    rename("updated.bin", "userinfo.bin");

    return 0;

}

