#include <stdio.h>
#include <string.h>
#include <argon2.h>

int main(void)
{
    const char *password = "TestPassword123!";
    const char *wrongPassword = "WrongPassword123!";
    const char *salt = "0123456789abcdef";

    char hash[128];

    int result = argon2id_hash_encoded(
        3,              // time cost
        65536,          // memory cost: 64 MiB
        1,              // parallelism
        password,
        strlen(password),             // password length
        salt,
        strlen(salt),             // salt length
        32,             // hash length
        hash,
        sizeof(hash)
    );

    if (result != ARGON2_OK)
    {
        printf("Argon2 error: %s\n", argon2_error_message(result));
        return 1;
    }

    printf("Hash:\n%s\n\n", hash);

    /* Verify correct password */
    result = argon2id_verify(hash, password, 16);

    if (result == ARGON2_OK)
        printf("Correct password: VERIFIED\n");
    else
        printf("Correct password: FAILED\n");

    /* Verify wrong password */
    result = argon2id_verify(hash, wrongPassword, 17);

    if (result == ARGON2_OK)
        printf("Wrong password: VERIFIED\n");
    else
        printf("Wrong password: REJECTED\n");

    return 0;
}