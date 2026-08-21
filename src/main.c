#include <stdio.h>

#include "auth.h"
#include "input.h"

int main() {
    int running = 1;
    while (running)
    {
        printf("\n===== Secure Authentication =====\n");
        printf("Choose Service:\n");
        printf("1. Register\n");
        printf("2. Login\n");
        printf("3. Exit\n");

        printf("Choose an option: ");
        int choiceMenu = readChoice(1, 3);

        switch(choiceMenu)
        {
            case 1:
                printf("Registration selected... \n");
                authResult regResult = registerUser();
                if (regResult == AUTH_CANCELLED) { printf("\n-Returned To Main Menu-\n"); }
                if (regResult == AUTH_FAILURE) { printf("\n--Fatal Error: Unexpected/internal/input failure!--\n"); }
                break;

            case 2:
                printf("Login selected... \n");
                authResult loginResult = loginUser();
                if(loginResult == AUTH_CANCELLED) { printf("\n-Returned To Main Menu-\n"); }
                if (loginResult == AUTH_FAILURE) { printf("\n--Fatal Error: Unexpected/Internal/Input Failure!--\n"); }
                break;

            case 3:
                printf("Exit selected... Farewell!\n");
                running = 0;
                break;

            default:
                printf("Invalid selection!\n");
                break;
        }
    }
    return 0;
}
