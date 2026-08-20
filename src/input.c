#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "input.h"

inputResult readLine(char* buffer, size_t size) {
    // checks if error/failure occured when fgetting input (EOF, input error...)
    if (fgets(buffer, size, stdin) == NULL)
    {
        return INPUT_TOO_LONG;
    }
    
    // chech buffer overflow and flush overflow characters
    size_t length = strlen(buffer);

    if (length > 0 && buffer[length-1] != '\n')
    {
        int character;
        while ((character = getchar()) != '\n' && character != EOF)
        {
            // discard remaining chars
        }
        return INPUT_TOO_LONG;
    }

    if (length > 0 && buffer[length - 1] == '\n')
    {
        buffer[length - 1] = '\0';
    }

    return INPUT_OK;
}

int readChoice(int min, int max) {

    char buffer[3];

    if (readLine(buffer, sizeof(buffer)) == INPUT_TOO_LONG) { return -1; }
    if (!isdigit((unsigned char)buffer[0])) { return -1; }

    int choice = buffer[0] - '0';

    if (choice < min || choice > max || buffer[1] != '\0') { return -1; }
    return choice;
}
