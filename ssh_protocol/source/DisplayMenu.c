#include<stdio.h>
int ssh();
void ReadInfo();
void update_entry(void);
int ExistingUser();
int RemoveInfo();

int main()
{
    system("clear");
    int n;
    while(n != 6)
    {
    printf("\n");
    printf("============= MENU =============\n");
    printf("1 : New User\n2 : Existing User\n3 : Read Info\n4 : Edit Info\n5 : Remove Info\n6 : Exit program\n");
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
            //printf("Existing Usre\n");
            ReadInfo();
            ExistingUser();
            break;

        case 3:
            ReadInfo();
            break;

        case 4:
            update_entry();
            break;

        case 5:
            RemoveInfo();
            break;

        case 6:
               printf("Exiting...\n");
               break;

        default:
               printf("You have selected invalid option !!\n\n");
    }
    }

    return 0;

}
