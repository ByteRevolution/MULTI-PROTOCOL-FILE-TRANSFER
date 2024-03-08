#include<stdio.h>
int ssh();
void ReadInfo();

int main()
{
    system("clear");
    int n;
    while(n != 5)
    {
    printf("\n");
    printf("============= MENU =============\n");
    printf("1 : New User\n2 : Existing User\n3 : Read Info\n4 : Remove Info\n5 : Exit program\n");
    printf("================================\n");
    printf("Enter number according to what you have to do: ");
    scanf("%d",&n);
    getchar();
    switch(n)
    {
        case 1:
            ssh();
            break;

        case 2:
            printf("Existing Usre\n");
            break;

        case 3:
            ReadInfo();
            break;

        case 4:
            printf("Removing Data...\n");
            system("sleep 1");
            const char path[]="./userinfo.bin";
            remove(path);
            const char path1[]="./serial_number.txt";
            remove(path1);
            break;

        case 5:
               printf("Exiting...\n");
               break;

        default:
               printf("You have selected invalid option !!\n\n");
    }
    }

    return 0;

}
