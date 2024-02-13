#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <windows.h>
#include <string.h>

#define MAX_NAME_LEN 20
#define MAX_PASSWORD_LEN 20
#define MAX_ACCOUNTS 100

struct User
{
    char name[MAX_NAME_LEN];
    int identification;
    int clientContact;
    char passWord [MAX_PASSWORD_LEN];
};

struct User newUser[MAX_ACCOUNTS];
int numAccounts = 0;


void createAccount();

bool checkIdentificationExist(int identification);

void homePage();

bool login(const char* username, const char* passWord);

bool adminAccount(const char* name, const char* password);

int main()
{
    homePage();

}
void homePage()
{
    char name [MAX_NAME_LEN];
    char passWord;

    int choice;

    printf("Hello! Welcome to KITABU LIBRARY.\n");
    printf("Kindly select preferred operation.\n");
    printf("1. CREATE ACCOUNT \n2. LOGIN TO YOUR ACCOUNT\n");

    scanf("%d", &choice);

    switch(choice)
    {
    case 1:
        createAccount();
        break;
    case 2:
        printf("Enter your Name: ");
        scanf("%s", name);
        printf("Enter your password: ");
        scanf("%s", &passWord);

        login(name, &passWord);
        break;

    default:
        printf("Invalid input. Don't be a bastard!");
        homePage();
    }

    //printf("Would you like to return to HomePage?");

    return;
}

void createAccount(){
    char name [MAX_NAME_LEN];
    char passWord;

    if (numAccounts >= MAX_ACCOUNTS){
        printf("System is full. You cannot create an account at this time. Kindly visit our customer service desk for more assistance");

        homePage();

        return;
    }

    printf("Enter your username: \n");
    scanf("%s", newUser[numAccounts].name);

    printf("Enter your ID Number: \n");
    scanf("%d", &newUser[numAccounts].identification);

    printf("Enter your password: \n");
    scanf("%s", &newUser[numAccounts].passWord);

     if (checkIdentificationExist(newUser[numAccounts].identification)) {
        printf("Error: User with the same ID already exists.\n");
        printf("REDIRECTING!\n");

        Sleep(5000);

        homePage();

        return;
    }
    FILE *fclient;
    //struct User user;

    fclient = fopen("clientlist.txt", "a");

    if (fclient == NULL) {
        printf("Error opening the file.\n");
        return;
    }

    fprintf(fclient, "%s %d %s\n", newUser[numAccounts].name, newUser[numAccounts].identification, &newUser[numAccounts].passWord);
    fclose(fclient);

    printf("Account created successfully.\n");

    numAccounts++;

    printf("You are being redirected back to the Homepage.");

    Sleep(5000);

    homePage();

}

bool checkIdentificationExist (int identification)
{
      FILE *file = fopen("clientlist.txt", "r");
    if (file == NULL)
    {
        printf("Error opening file.\n");
        return false;
    }

    struct User tempUser;
    while (fscanf(file, "%s %d %s", tempUser.name, &tempUser.identification, &tempUser.passWord) == 3)
    {
        if (tempUser.identification == identification)
        {
             fclose(file);
            return true;
        }
    }
fclose(file);
return false;
}

bool login(const char *name, const char *password)
{
    for (int i = 0; i < numAccounts; ++i)
    {
        if (strcmp(name, newUser[i].name) == 0)
        {
            if (strcmp(password, newUser[i].passWord) == 0)
            {
                printf("You have logged in successfully.\n");
                return true;
            }
            else
            {
                adminAccount(name, password);
            }
            // Matching username found, but incorrect password
        }
    }

    // If the loop completes without finding a match
    printf("User not found. Please recheck your credentials and try again!\n");
    printf("REDIRECTING!\n");
    Sleep(5000);
    homePage(); //
}

bool adminAccount(const char* name, const char* password)
{
    const char* adminName = "kitabuLibrary";
    const char* adminPassWord = "Lib2024";

     for (int i = 0; i < numAccounts; ++i)
    {
        if (strcmp(name, newUser[i].name) == 0)
        {
            if (strcmp(password, newUser[i].passWord) == 0)
            {
                 printf("You have logged in successfully into the Administrator's Account!.\n");
                 return true;
            }
            else
            {
                printf("Incorrect password. Please recheck your credentials and try again!\n");
                return false;
            }
        }
    }
}



