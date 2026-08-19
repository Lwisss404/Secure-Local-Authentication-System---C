#include <stdio.h>

int main() {

    int choice;

    printf("\n===== Secure Authentication =====\n");
    printf("Choose Service:\n");
    printf("1. Register\n");
    printf("2. Login\n");
    printf("3. Exit\n");

    printf("Choose an option: ");
    scanf("%d", &choice);

    switch(choice)
    {
        case 1:
            printf("Registration selected... \n");
            break;

        case 2:
            printf("Login selected... \n");
            break;

        case 3:
            printf("Exit selected... Farewell!\n");
            break;

        default:
            printf("Invalid selection!\n");
            break;
    }

    return 0;
}