#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "storage.h"
#include "argon2.h"

#define DATABASE_FILE "users.db"
#define SALT_LENGTH 16
#define HASHED_PASSWORD_LENGTH 98

int usernameExists(const char* username) {

    FILE *file = fopen(DATABASE_FILE, "r");

    if (file == NULL)
    {
        return 0;
    }

    char storedUsername [32 + 1];
    char storedPassword [HASHED_PASSWORD_LENGTH + 1];

    while (fscanf(file, " %32[^:]:%98s", storedUsername, storedPassword) == 2)
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

    /* generating salt for the hashing of the password */
    unsigned char salt[SALT_LENGTH];
    arc4random_buf(salt, sizeof(salt));

    /* hashing password */
    char hash [128];
    int result = argon2id_hash_encoded(
        3,                      // Time cost
        65536,                  // Memory cost
        1,                      // Threads cost (parallelism)
        password,
        strlen(password),       // Password length
        salt,
        SALT_LENGTH,            // Salt length
        32,                     // Hash length
        hash,
        sizeof(hash)
    );

    if (result != ARGON2_OK) 
    {
        printf("Argon2 error: %s\n", argon2_error_message(result));
        return 0;
    }

    fprintf(file, "%s:%s\n", username, hash);

    fclose(file);

    return 1;
}

int verifyCredentials(const char* username, const char* password){

    FILE *file = fopen(DATABASE_FILE, "r");

    if (file == NULL) { return 0; }

    char storedUsername [32 + 1];
    char storedPassword [HASHED_PASSWORD_LENGTH + 1];

    while (fscanf(file, " %32[^:]:%98s", storedUsername, storedPassword) == 2)
    {
        if (strcmp(username, storedUsername) == 0 && argon2id_verify(storedPassword, password, strlen(password)) == ARGON2_OK)
        {
            fclose(file);
            return 1;
        }
    }
    fclose(file);
    return 0;
}
