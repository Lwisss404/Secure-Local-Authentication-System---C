#include <stdio.h>
#include <string.h>

#include "storage.h"

#define DATABASE_FILE "users.db"

int usernameExists(const char* username) {

    FILE *file = fopen(DATABASE_FILE, "r");

    if (file == NULL)
    {
        return 0;
    }

    char storedUsername [32 + 1];
    char storedPassword [128 + 1];

    while (fscanf(file, " %32[^:]:%128s", storedUsername, storedPassword) == 2)
    {
        if (strcmp(username, storedUsername) == 0)
        {
            fclose(file);
            return 1;
        }
    }

    fclose(file);
    return 0;
}

int saveUser(const char* username, const char* password) {

    FILE *file = fopen(DATABASE_FILE, "a");

    if (file == NULL)
    {
        return 0;
    }

    fprintf(file, "%s:%s\n", username, password);

    fclose(file);

    return 1;
}

int verifyCredentials(const char* username, const char* password){

    FILE *file = fopen(DATABASE_FILE, "r");

    if (file == NULL) { return 0; }

    char storedUsername [32 + 1];
    char storedPassword [128 + 1];

    while (fscanf(file, " %32[^:]:%128s", storedUsername, storedPassword) == 2)
    {
        if (strcmp(username, storedUsername) == 0 && strcmp(password, storedPassword) == 0)
        {
            fclose(file);
            return 1;
        }
    }
    fclose(file);
    return 0;
}