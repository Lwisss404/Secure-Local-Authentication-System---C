#include <stdio.h>
#include <ctype.h>
#include <string.h>

#include "validation.h"
#include "auth.h"
#include "storage.h"

#define MAX_USERNAME_LENGTH 32
#define MIN_PASSWORD_LENGTH 16
#define MAX_PASSWORD_LENGTH 128


usernameValidationResult validateUsername(const char* username) {

    /* result is a bitmask containing a flag for each possible error */
    usernameValidationResult result = VALID_USERNAME;
    size_t length = strlen(username);

    /* assign corresponding bits to indicate the occurrance of error */
    if (length == 0) { result |= USERNAME_EMPTY; }
    if (length > MAX_USERNAME_LENGTH) { result |= USERNAME_TOO_LONG; }

    /* check for  for occurrance in username */
    for (size_t i = 0; i < length; i++)
    {
        if(!isalnum((unsigned char)username[i]) && username[i] != '_') { result |= USERNAME_INVALID_CHARACTERS; break;}
    }

    return result;
}


passwordValidationResult validatePassword(const char* password) {

    /* result is a bitmask containing a flag for each possible error */
    passwordValidationResult result = VALID_PASSWORD;
    size_t length = strlen(password);

    /* assign corresponding bits to indicate the occurrance of error */
    if (length < MIN_PASSWORD_LENGTH) { result |= PASSWORD_TOO_SHORT; }
    if (length > MAX_PASSWORD_LENGTH) { result |= PASSWORD_TOO_LONG; }

    /* character-type flags for occurrance in the password */
    int digitFlag = 0;
    int upperFlag = 0;
    int lowerFlag = 0;
    int specialFlag = 0;
    int spaceFlag = 0;

    /* list of special characters instead of using ASCII */
    const char* specialChars = "!@#$%^&*()-_=+[]{};:'\",.<>?/\\|";

    for (size_t i = 0; i < length; i++)
    {
        if (!digitFlag && isdigit((unsigned char)password[i])) { digitFlag = 1; }
        if (!upperFlag && isupper((unsigned char)password[i])) { upperFlag = 1; }
        if (!lowerFlag && islower((unsigned char)password[i])) { lowerFlag = 1; }
        if (!spaceFlag && isspace((unsigned char)password[i])) { spaceFlag = 1; }
        if (!specialFlag && strchr(specialChars, password[i]) != NULL) { specialFlag = 1; }
    }

    /* mask every error bit to result */
    if (!digitFlag) { result |= PASSWORD_NO_DIGIT; }
    if (!upperFlag) { result |= PASSWORD_NO_UPPERCASE; }
    if (!lowerFlag) { result |= PASSWORD_NO_LOWERCASE; }
    if (!specialFlag) { result |= PASSWORD_NO_SPECIAL; }
    if (spaceFlag) { result |= PASSWORD_HAS_SPACE; }

    return result;
}