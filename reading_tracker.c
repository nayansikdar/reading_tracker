#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<conio.h>
//login function
void account();
int login();


int main()
{
    int st;
    printf("due to privacy, you need log in first.\n\n press 1: If you don't have account\n press 2: log in\nEnter: ");
    scanf("%d",&st);
    if(st==1)
        account();
    else
    {
        if(login()==1)
        {
            printf("\npress 1: Current Book Status\npress 2: Add book on Wishlist");
            printf("\npress 3: Review and Ratings\npress 4: Reading History\n")
        }

    }

    return 0;
}

//login function
void account()
{
    printf("create account:\nuser name(single name,lowercase): ");
    //writing file
    FILE *account;
    account=fopen("account.txt","a");

    //taking name
    char name[100];
    scanf("%s",name);
    fputs(name,account);

    //taking pin
    printf("create PIN (4 digit): ");
    char pin[4];
    scanf("%s",pin);
    fputs(pin,account);
    fprintf(account," ");
    //closing file
    fclose(account);
    printf("\nYour account successfully created.\n");
}

//login function
int login()
{
    char nam[100];
    char cpynam[100];

    //inputing name
    printf("Enter user name: ");
    scanf("%s",nam);
    strcpy(cpynam,nam);

    //inputing pin
    char pass[100];
    printf("Enter PIN: ");
    scanf("%s",pass);

    //ading name and pin in one string
    strcat(nam,pass);

    //reading file
    FILE *account;
    account=fopen("account.txt","r");
    char name[500];
    fgets(name, 500, account);

    //finding name and pass
    if(strstr(name,nam)!=NULL)
    {
         system("cls");
        printf("hey %s, choose an option:\n",cpynam);
        return 1;
    }
    else
        printf("your account is not found.");

    //closing file
    fclose(account);
}
