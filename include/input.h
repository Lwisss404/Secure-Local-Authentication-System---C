#include <stddef.h>

#ifndef INPUT_H
#define INPUT_H

typedef enum {
    INPUT_OK,
    INPUT_TOO_LONG
} inputResult;

inputResult readLine(char* buffer, size_t size);
int readMenuChoice(void);

#endif