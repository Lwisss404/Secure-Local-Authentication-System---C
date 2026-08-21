#ifndef VALIDATION_H
#define VALIDATION_H

typedef enum {
    VALID_USERNAME = 0,
    USERNAME_EMPTY = 1 << 0,
    USERNAME_TOO_LONG = 1 << 1,
    USERNAME_INVALID_CHARACTERS = 1 << 2,
} usernameValidationResult;

usernameValidationResult validateUsername(const char* username);

typedef enum {
    VALID_PASSWORD = 0,
    PASSWORD_TOO_SHORT = 1 << 0,
    PASSWORD_TOO_LONG = 1 << 1,
    PASSWORD_NO_LOWERCASE = 1 << 2,
    PASSWORD_NO_UPPERCASE = 1 << 3,
    PASSWORD_NO_DIGIT = 1 << 4,
    PASSWORD_NO_SPECIAL = 1 << 5,
    PASSWORD_HAS_SPACE = 1 << 6
} passwordValidationResult;

passwordValidationResult validatePassword(const char* password);

#endif
