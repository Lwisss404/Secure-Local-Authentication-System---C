#include <stdio.h>
#include <string.h>

#include "auth.h"
#include "validation.h"
#include "storage.h"
#include "input.h"

#define USERNAME_BUFFER_SIZE 64
#define PASSWORD_BUFFER_SIZE 160


void registerUser(void) {
    
    char username [USERNAME_BUFFER_SIZE];
    char password [PASSWORD_BUFFER_SIZE];

    printf("\n===== Register =====\n");

    printf("\nUsername: ");
    /* verify username length and handle stdin overflow */
    inputResult resultInputUsername = readLine(username, sizeof(username));
    if (resultInputUsername == INPUT_TOO_LONG)
    {
        printf("\nError: Username Input Too Long!\n");
        return;
    }

    /* verify non empty, lengthy, valid characters username */
    usernameValidationResult resultValUser = validateUsername(username);
    if (resultValUser & USERNAME_EMPTY) { printf("Error: Username Empty\n"); }
    if (resultValUser & USERNAME_TOO_LONG) { printf("Error: Username Too Long\n"); }
    if (resultValUser & USERNAME_INVALID_CHARACTERS) { printf("Error: Username Contains Invalid Characters!\n"); }
    if (resultValUser == VALID_USERNAME)
    { 
        /* check if username exist already in the database */
        if (usernameExists(username)) { printf("Error: Username Exists In Database!\n"); return; }
        else { printf("Valid Username!\n"); } 
    }

    printf("\nPassword: ");
    /* verify password length and handle stdin overflow */
    inputResult resultInputPassword = readLine(password, sizeof(password));
    if (resultInputPassword == INPUT_TOO_LONG)
    {
        printf("\nError: Password Input Too Long!\n");
        return;
    }

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
        } else 
        {
            printf("Error with the registration, please try again!");
        }
    }
}