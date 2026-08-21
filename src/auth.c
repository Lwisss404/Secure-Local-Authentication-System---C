#include <stdio.h>
#include <string.h>

#include "auth.h"
#include "validation.h"
#include "storage.h"
#include "input.h"

#define USERNAME_BUFFER_SIZE 64
#define PASSWORD_BUFFER_SIZE 160


authResult registerUser(void) {
    
    char username [USERNAME_BUFFER_SIZE];
    char password [PASSWORD_BUFFER_SIZE];

    printf("\n===== Register =====\n");
    printf("0. Back\n");
    printf("1. Continue\n");

    /* menu for going back to main menu in case of misinput */
    while (1) {
        printf("Choose an option: ");
        int choiceNav = readChoice(0, 1);
        switch (choiceNav)
        {
            case 0: printf("\nReturning To Main Menu...\n"); return AUTH_CANCELLED;
            case 1: printf("\nContinuing...\n"); break;
            default: printf("\nWrong Option!\n"); continue;
        }
        break;
    }

    while (1)
    {
        printf("\nUsername: ");
        /* verify username length and handle stdin overflow */
        inputResult resultInputUsername = readLine(username, sizeof(username));
        if (resultInputUsername == INPUT_ERROR) {printf("\nError: Error Reading Username!\n"); return AUTH_FAILURE;}
        if (resultInputUsername == INPUT_TOO_LONG) { printf("\nError: Username Input Too Long!\n"); return AUTH_FAILURE; }
        

        /* verify non empty, lengthy, valid characters username */
        usernameValidationResult resultValUser = validateUsername(username);
        int usernameExistsInDB = usernameExists(username);
        if (resultValUser & USERNAME_EMPTY) { printf("Error: Username Empty\n"); }
        if (resultValUser & USERNAME_TOO_LONG) { printf("Error: Username Too Long\n"); }
        if (resultValUser & USERNAME_INVALID_CHARACTERS) { printf("Error: Username Contains Invalid Characters!\n"); }
        if (resultValUser == VALID_USERNAME && !usernameExistsInDB) { printf("Valid Username!\n"); break; }
        else {
            if (usernameExistsInDB) { printf("Error: Username Exists In Database, Try Again!\n");}
            printf("\n0. Back\n");
            printf("1. Try Again\n");
            while (1)
            {
                printf("Choose an option: ");
                int choiceUser = readChoice(0, 1);
                
                switch (choiceUser)
                {
                    case 0: printf("\nReturning To Main Menu...\n"); return AUTH_CANCELLED;
                    case 1: printf("\nTrying Again...\n"); break;
                    default: printf("\nWrong Option!\n"); continue;
                }
                break;
            }
        }
    }

    while (1)
    {
        printf("\nPassword: ");
        /* verify password length and handle stdin overflow */
        inputResult resultInputPassword = readLine(password, sizeof(password));
        if (resultInputPassword == INPUT_ERROR) {printf("\nError: Error Reading Password!\n"); return AUTH_FAILURE;}
        if (resultInputPassword == INPUT_TOO_LONG) { printf("\nError: Password Input Too Long!\n"); return AUTH_FAILURE; }

        /* verify valid length, valid characters password */
        passwordValidationResult resultValPass = validatePassword(password);
        if (resultValPass & PASSWORD_TOO_SHORT) { printf("Error: Password Too Short!\n"); }
        if (resultValPass & PASSWORD_TOO_LONG) { printf("Error: Password Too Long!\n"); }
        if (resultValPass & PASSWORD_NO_DIGIT) { printf("Error: Password Must Contain At Least 1 Digit!\n"); }
        if (resultValPass & PASSWORD_NO_UPPERCASE) { printf("Error: Password Must Contain At Least 1 Uppercase Character!\n"); }
        if (resultValPass & PASSWORD_NO_LOWERCASE) { printf("Error: Password Must Contain At Least 1 Lowercase Character!\n"); }
        if (resultValPass & PASSWORD_NO_SPECIAL) { printf("Error: Password Must Contain At Least 1 Special Character!\n"); }
        if (resultValPass & PASSWORD_HAS_SPACE) { printf("Error: Password Must NOT Contain Spaces!\n"); }
        
        if (resultValPass == VALID_PASSWORD)
        {
            if (saveUser(username, password))
            {
                printf("\n===== Registration Successful =====\n");
                printf("Welcome.. %s!\n", username);
                return AUTH_SUCCESS;
            } else 
            {
                printf("Error with the registration, please try again!");
                return AUTH_FAILURE;
            }
        }
        printf("\n0. Back\n");
        printf("1. Try Again\n");
        while (1)
        {
            printf("Choose an option: ");
            int choiceUser = readChoice(0, 1);
            
            switch (choiceUser)
            {
                case 0: printf("\nReturning To Main Menu...\n"); return AUTH_CANCELLED;
                case 1: printf("\nTrying Again...\n"); break;
                default: printf("\nWrong Option!\n"); continue;
            }
            break;
        }
    }
}


authResult loginUser(void) {

    char username[USERNAME_BUFFER_SIZE];
    char password[PASSWORD_BUFFER_SIZE];

    printf("\n===== Log In =====\n");
    printf("0. Back\n");
    printf("1. Continue\n");

    /* menu for going back to main menu in case of misinput */
    while (1) {
        printf("Choose an option: ");
        int choiceNav = readChoice(0, 1);
        switch (choiceNav)
        {
            case 0: printf("\nReturning To Main Menu...\n"); return AUTH_CANCELLED;
            case 1: printf("\nContinuing...\n"); break;
            default: printf("\nWrong Option!\n"); continue;
        }
        break;
    }

    while (1) 
    {
        printf("\nUsername: ");
        inputResult resultInputUsername = readLine(username, sizeof(username));
        /* verify username length and handle stdin overflow */
        if (resultInputUsername == INPUT_ERROR) {printf("\nError: Error Reading Username!\n"); return AUTH_FAILURE;}
        if (resultInputUsername == INPUT_TOO_LONG) {printf("\nError: Username Too Long!\n"); return AUTH_FAILURE;}

        printf("\nPassword: ");
        inputResult resultInputPassword = readLine(password, sizeof(password));
        /* verify password length and handle stdin overflow */
        if (resultInputPassword == INPUT_ERROR) {printf("\nError: Error Reading Password!\n"); return AUTH_FAILURE;}
        if (resultInputPassword == INPUT_TOO_LONG) {printf("\nError: Password Too Long!\n"); return AUTH_FAILURE;}

        if (!verifyCredentials(username, password)) {
            printf("\nError: Account Couldn't Be Found Or Wrong Password!\n Try Again...\n");
            printf("\n0. Back\n");
            printf("1. Try Again\n");
            while (1)
            {
                printf("Choose an option: ");
                int choiceUser = readChoice(0, 1);
                
                switch (choiceUser)
                {
                    case 0: printf("\nReturning To Main Menu...\n"); return AUTH_CANCELLED;
                    case 1: printf("\nTrying Again...\n"); break;
                    default: printf("\nWrong Option!\n"); continue;
                }
                break;
            }
        } else {
            printf("\n===== Login Successful =====\n");
            printf("Welcome back, %s!\n", username);
            return AUTH_SUCCESS;
        }
    }
}
