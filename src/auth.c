#include <stdio.h>
#include <string.h>

#include "auth.h"
#include "storage.h"

#define MAX_USERNAME_LENGTH 32
#define MAX_PASSWORD_LENGTH 128

void registerUser(void) {
    
    char username [MAX_USERNAME_LENGTH + 1];
    char password [MAX_PASSWORD_LENGTH + 1];

    printf("\n===== Register =====\n");

    printf("\nUsername: ");
    scanf("%32s", username);

    if (usernameExists(username))
    {
        printf("Username already exists!\n");
        return;
    }

    printf("\nPassword: ");
    scanf("%128s", password);

    if (saveUser(username, password))
    {
        printf("\n===== Registration Successful =====\n");
        printf("Welcome.. %s!\n", username);
    } else 
    {
        printf("Error with the registration, please try again!");
    }
}