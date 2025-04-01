#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<conio.h>
//login function
void account();
int login();

//option function
int option();

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
           option();
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



int option() {
    int opt;
    printf("\nSelect an option:\n");
    printf("1: Current Book Status\n");
    printf("2: Add book to Wishlist\n");
    printf("3: Review and Ratings\n");
    printf("4: Reading History\n");
    printf("Enter your choice: ");
    scanf("%d", &opt);
    getchar(); // To consume the newline character after scanf

    if (opt == 1) {
        system("cls"); // Clear the screen (Note: This works in Windows, use system("clear") on Linux)

        // Open the file to check if the user is reading a book
        FILE *book = fopen("current_book.txt", "r");

        if (book == NULL) {
            // If file doesn't exist, prompt the user to add a book
            printf("You are not currently reading any book. Please add a book:\n");

            // Open file to write the new book information
            book = fopen("current_book.txt", "w");

            if (book == NULL) {
                printf("Error opening file to write. Exiting.\n");
                return 1;
            }

            // Taking book name
            printf("Enter Book Name: ");
            char booknam[100];
            fgets(booknam, 100, stdin);
            booknam[strcspn(booknam, "\n")] = '\0'; // Remove the newline

            fprintf(book, "Book Name: %s\n", booknam);

            // Taking author name
            printf("Enter Author Name: ");
            char authnam[100];
            fgets(authnam, 100, stdin);
            authnam[strcspn(authnam, "\n")] = '\0'; // Remove the newline

            fprintf(book, "Author Name: %s\n", authnam);

            // Taking page number
            printf("Enter Page Number: ");
            int page;
            scanf("%d", &page);
            fprintf(book, "Page Number: %d\n", page);

            fclose(book); // Close the file after writing
            printf("Book has been added successfully.\n");

        } else {
            // If file exists, read and display the current book details
            char line[500];
            int paused = 0;
            int pausedPage = 0;
            printf("Currently reading a book. Here are the details:\n");

            while (fgets(line, sizeof(line), book)) {
                printf("%s", line); // Print each line read from the file

                // Check if the book is paused
                if (strstr(line, "Paused at page:") != NULL) {
                    paused = 1;
                    sscanf(line, "Paused at page: %d", &pausedPage);
                }
            }

            fclose(book); // Close the file after reading

            if (paused) {
                // If the reading was paused, display the page where it was paused
                printf("\nReading was paused at page %d.\n", pausedPage);
                printf("Select an option:\n");
                printf("1: Resume Reading\n");
                printf("2: Mark as Finished\n");
                printf("3: Pause Reading\n");
                int action;
                scanf("%d", &action);

                if (action == 1) {
                    // Resume the reading from the paused page
                    book = fopen("current_book.txt", "a");
                    if (book == NULL) {
                        printf("Error opening file for resuming. Exiting.\n");
                        return 1;
                    }
                    fprintf(book, "Resumed from page: %d\n", pausedPage);
                    fclose(book);
                    printf("Resumed reading from page %d.\n", pausedPage);
                } else if (action == 2) {
                    // Mark as finished - Clear the file
                    remove("current_book.txt");
                    printf("Book marked as finished.\n");
                } else if (action == 3) {
                    // Pause reading again - Ask how many pages were read
                    printf("Enter the page number you finished reading: ");
                    int pageRead;
                    scanf("%d", &pageRead);

                    // Update the file with paused page number
                    book = fopen("current_book.txt", "a");
                    if (book == NULL) {
                        printf("Error opening file to pause reading. Exiting.\n");
                        return 1;
                    }
                    fprintf(book, "Paused at page: %d\n", pageRead);
                    fclose(book);
                    printf("Reading paused at page %d.\n", pageRead);
                }

            } else {
                // If reading is not paused, give options to pause or finish
                printf("\nSelect an option:\n");
                printf("1: Mark as Finished\n");
                printf("2: Pause Reading\n");
                int action;
                scanf("%d", &action);

                if (action == 1) {
                    // Mark as finished - Clear the file
                    remove("current_book.txt");
                    printf("Book marked as finished.\n");
                } else if (action == 2) {
                    // Pause reading - Ask how many pages were read
                    printf("Enter the page number you finished reading: ");
                    int pageRead;
                    scanf("%d", &pageRead);

                    // Update the file with paused page number
                    book = fopen("current_book.txt", "a");
                    if (book == NULL) {
                        printf("Error opening file to pause reading. Exiting.\n");
                        return 1;
                    }
                    fprintf(book, "Paused at page: %d\n", pageRead);
                    fclose(book);
                    printf("Reading paused at page %d.\n", pageRead);
                }
            }
        }
    }
}





