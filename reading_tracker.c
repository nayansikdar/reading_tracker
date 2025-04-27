#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<conio.h>

// Functions
void account();
int login();
int option();
int option_1();
int option_2();
int option_3();

//Global variable & fucntion
char username[100];
char file_current[120];
char file_wishlist[120];
char file_history[120];
void fliename()
{
    sprintf(file_current, "%s_current_book.txt", username);
    sprintf(file_wishlist, "%s_wishlist.txt", username);
    sprintf(file_history, "%s_reading_history.txt", username);
}

//main function
int main()
{
    int st;
    printf("Due to privacy, you need to log in first.\n\n");
    printf("Press 1: If you don't have an account\n");
    printf("Press 2: Log in\nEnter: ");
    scanf("%d", &st);

    if(st == 1)
        account();
    else if(st == 2)
    {
        if(login() == 1)
        {
            option();
        }
    }

    else
        printf("\nwrong input.\n");

    return 0;
}

// Creating account
void account()
{
    printf("Create account:\nUsername (lowercase, single word): ");
    char name[100];
    scanf("%s", name);

    printf("Create 4-digit PIN: ");
    char pin[5];
    scanf("%s", pin);

    FILE *account = fopen("account.txt", "a");
    fputs(name, account);
    fputs(pin, account);
    fprintf(account, " ");
    fclose(account);

    printf("\nYour account has been successfully created.\nPlease rerun code and login. THANK YOU!\n");
}

// Login function
int login()
{
    char nam[100];
    char pass[100];

    printf("Enter username: ");
    scanf("%s", nam);
    //copy name into global variable
    strcpy(username, nam);

    printf("Enter PIN: ");
    scanf("%s", pass);

    //name&pin adding
    strcat(nam, pass);

    //reading file
    FILE *account;
    account=fopen("account.txt","r");
    char name[500];
    fgets(name, 500, account);

    //checking name and pass
    if(strstr(name,nam)!=NULL)
    {
        system("cls");
        printf("hey %s, choose an option:\n",username);
        return 1;
    }
    else
        printf("\nyour account is not found.\n");

    //closing file
    fclose(account);
}

// Main menu and logic

int option()
{
    int opt;
    fliename();


    while (1)
    {
        printf("\n=== Main Menu ===\n");
        printf("1: Current Book Status\n");
        printf("2: Add Book to Wishlist\n");
        printf("3: Book Reading History\n");
        printf("4: Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &opt);
        getchar();

        if (opt == 1)
        {
            option_1();
        }
        else if (opt == 2)
        {
            option_2();
        }
        else if (opt == 3)
        {
            option_3();
        }
        else if (opt == 4)
        {
            printf("\n Goodbye!\n");
            break;
        }
        else
        {
            printf("Invalid option.\n");
            //last option
            printf("\n0: Main Menu\n9: Exit\nEnter:");
            int last;
            scanf("%d",&last);
            if(last==0)
                system("cls");
            else if(last==9)
            {
                printf("\n Goodbye!\n");
                exit(0);
            }
        }
    }
}

//sub function of option
int option_1()
{
    system("cls");
    FILE *book = fopen(file_current, "r");

    if (book == NULL)
    {
        printf("You are not currently reading any book.\n");

        FILE *wishlist = fopen(file_wishlist, "r");
        if (wishlist)
        {
            char line[500];
            printf("\nYour Wishlist:\n");
            while (fgets(line, sizeof(line), wishlist))
                printf("%s", line);
            fclose(wishlist);
        }
        else
            printf("Your wishlist is empty.\n");

        printf("\nEnter 1: Add a new book\n\n0: Main Menu\n9: Exit\nEnter: ");
        int choech;
        scanf("%d",&choech);
        getchar();
        if(choech==1)
        {
            book = fopen(file_current, "w");
            char booknam[100], authnam[100];
            int page;

            printf("Enter Book Name: ");
            fgets(booknam, 100, stdin);
            booknam[strcspn(booknam, "\n")] = '\0';

            printf("Enter Author Name: ");
            fgets(authnam, 100, stdin);
            authnam[strcspn(authnam, "\n")] = '\0';

            printf("Enter Page Number: ");
            scanf("%d", &page);
            getchar();

            fprintf(book, "Book Name: %s\nAuthor Name: %s\nPage Number: %d\n", booknam, authnam, page);
            fclose(book);

            printf("Book has been added successfully.\n");
            //last option
            printf("\n0: Main Menu\n9: Exit\nEnter: ");
            int last;
            scanf("%d",&last);
            if(last==0)
                system("cls");
            else if(last==9)
            {
                printf("\n Goodbye!\n");
                exit(0);
            }
        }

        //last option

        else if(choech==0)
            system("cls");
        else if(choech==9)
        {
            printf("\n Goodbye!\n");
            exit(0);
        }
        else
        {
            printf("wrong input.\n");
            //last option
            printf("\n0: Main Menu\n9: Exit\nEnter: ");
            int last;
            scanf("%d",&last);
            if(last==0)
                system("cls");
            else if(last==9)
            {
                printf("\n Goodbye!\n");
                exit(0);
            }
        }
    }
    else
    {
        char line[500];
        int paused = 0, pausedPage = 0;
        printf("Current Book Details:\n");
        while (fgets(line, sizeof(line), book))
        {
            printf("%s", line);
            if (strstr(line, "Paused at page:"))
                sscanf(line, "Paused at page: %d", &pausedPage), paused = 1;
        }
        fclose(book);
        printf("\nOptions:\n");
        if (paused) printf("Enter 1: Resume Reading\n");
        printf("Enter 2: Mark as Finished\n");
        printf("Enter 3: Pause Reading\n");
        printf("\n0: Main Menu\n9: Exit\nEnter: ");
        int action;
        scanf("%d", &action);
        getchar();

        if (paused && action == 1)
        {
            book = fopen(file_current, "a");
            fprintf(book, "Resumed from page: %d\n", pausedPage);
            fclose(book);
            printf("Resumed reading from page %d.\n", pausedPage);

            //last option
            printf("\n0: Main Menu\n9: Exit\nEnter:");
            int last;
            scanf("%d",&last);
            if(last==0)
                system("cls");
            else if(last==9)
            {
                printf("\n Goodbye!\n");
                exit(0);
            }
        }
        else if (action == 2)
        {
            FILE *history = fopen(file_history, "a");
            book = fopen(file_current, "r");

            char bookDetails[500];
            while (fgets(bookDetails, sizeof(bookDetails), book))
                fputs(bookDetails, history);
            fclose(book);
            fclose(history);

            remove(file_current);
            printf("Book marked as finished.\n");

            printf("Rate the book (1-5): ");
            int rating;
            scanf("%d", &rating);
            getchar();

            printf("Write a review: ");
            char review[500];
            fgets(review, sizeof(review), stdin);
            review[strcspn(review, "\n")] = '\0';

            history = fopen(file_history, "a");
            fprintf(history, "Rating: %d/5\nReview: %s\n\n", rating, review);
            fclose(history);
            //last option
            printf("\n0: Main Menu\n9: Exit\nEnter:");
            int last;
            scanf("%d",&last);
            if(last==0)
                system("cls");
            else if(last==9)
            {
                printf("\n Goodbye!\n");
                exit(0);
            }
        }
        else if (action == 3)
        {
            printf("Enter the page you paused at: ");
            int page;
            scanf("%d", &page);
            getchar();

            book = fopen(file_current, "a");
            fprintf(book, "Paused at page: %d\n", page);
            fclose(book);
            printf("Reading paused at page %d.\n", page);
            //last option
            printf("\n0: Main Menu\n9: Exit\nEnter:");
            int last;
            scanf("%d",&last);
            if(last==0)
                system("cls");
            else if(last==9)
            {
                printf("\n Goodbye!\n");
                exit(0);
            }
        }
        if(action==0)
            system("cls");
        else if(action==9)
        {
            printf("\n Goodbye!\n");
            exit(0);
        }
    }
}

//sub function of option
int option_2()
{
    system("cls");
    FILE *wishlist = fopen(file_wishlist, "r");
    if (wishlist!=NULL)
    {
        char line[500];
        printf("Your Wishlist:\n");
        while (fgets(line, sizeof(line), wishlist))
            printf("%s", line);
        fclose(wishlist);
        printf("\nEnter 1: Add a book to your wishlist\nEnter 2: Remove all books from wishlist\n\n0: Main Menu\n9: Exit\nEnter:Please Enter: ");
        int choice;
        scanf(" %d", &choice);
        getchar();
        if (choice == 1)
        {
            wishlist = fopen(file_wishlist, "a");
            char booknam[100], authnam[100];
            int page;

            printf("Enter Book Name: ");
            fgets(booknam, 100, stdin);
            booknam[strcspn(booknam, "\n")] = '\0';

            printf("Enter Author Name: ");
            fgets(authnam, 100, stdin);
            authnam[strcspn(authnam, "\n")] = '\0';

            printf("Enter Page Number: ");
            scanf("%d", &page);
            getchar();

            fprintf(wishlist, "Book Name: %s\nAuthor Name: %s\nPage Number: %d\n\n", booknam, authnam, page);
            fclose(wishlist);

            printf("Book added to wishlist.");
            //last option
            printf("\n\n0: Main Menu\n9: Exit\nEnter:");
            int last;
            scanf("%d",&last);
            if(last==0)
                system("cls");
            else if(last==9)
            {
                printf("\n Goodbye!\n");
                exit(0);
            }

        }
        else if(choice==2)
        {
            printf("\nSuccessfully Removed");
            remove(file_wishlist);
            //last option
            printf("\n\n0: Main Menu\n9: Exit\nEnter:");
            int last;
            scanf("%d",&last);
            if(last==0)
                system("cls");
            else if(last==9)
            {
                printf("\n Goodbye!\n");
                exit(0);
            }
        }
        //last option
        if(choice==0)
            system("cls");
        else if(choice==9)
        {
            printf("\n Goodbye!\n");
            exit(0);
        }
    }
    else
    {

        printf("Your wishlist is empty.\n");

        printf("\nEnter 1: Add a book to your wishlist\n\n0: Main Menu\n9: Exit\nPlease Enter: ");
        int choice;
        scanf(" %d", &choice);
        getchar();
        if (choice == 1)
        {
            wishlist = fopen(file_wishlist, "a");
            char booknam[100], authnam[100];
            int page;

            printf("Enter Book Name: ");
            fgets(booknam, 100, stdin);
            booknam[strcspn(booknam, "\n")] = '\0';

            printf("Enter Author Name: ");
            fgets(authnam, 100, stdin);
            authnam[strcspn(authnam, "\n")] = '\0';

            printf("Enter Page Number: ");
            scanf("%d", &page);
            getchar();

            fprintf(wishlist, "Book Name: %s\nAuthor Name: %s\nPage Number: %d\n\n", booknam, authnam, page);
            fclose(wishlist);

            printf("\nBook added to wishlist.\n");
            //last option
            printf("\n0: Main Menu\n9: Exit\nEnter:");
            int last;
            scanf("%d",&last);
            if(last==0)
                system("cls");
            else if(last==9)
            {
                printf("\n Goodbye!\n");
                exit(0);
            }

        }
        else if(choice==0)
            system("cls");
        else if(choice==9)
        {
            printf("\n Goodbye!\n");
            exit(0);
        }
        else
            printf("Invalid Input.");
    }

}

//sub function of option
int option_3()
{
    system("cls");


//Arnob Sarker's code start
    FILE *history = fopen(file_history, "r");
    if (history == NULL)
    {
        printf("No reading history found.\n");
    }
    else
    {
        char line[500];
        printf("Reading History:\n");
        while (fgets(line, sizeof(line), history))
            printf("%s", line);
        fclose(history);
    }
//Arnon Sarker's code end


    //last option
    printf("\n0: Main Menu\n9: Exit\nEnter:");
    int last;
    scanf("%d",&last);
    if(last==0)
        system("cls");
    else if(last==9)
    {
        printf("\n Goodbye!\n");
        exit(0);
    }

}

