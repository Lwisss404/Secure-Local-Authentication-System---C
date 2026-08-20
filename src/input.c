#include <stdio.h>
#include <string.h>

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

int readMenuChoice(void) {

    char buffer[2];

    readLine(buffer, sizeof(buffer));

    if (buffer[0] < '1' || buffer[0] > '3' || buffer[1] != '\0') { return -1; }
    return buffer[0] - '0';
}