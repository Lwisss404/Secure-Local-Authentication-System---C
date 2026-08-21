#include <stddef.h>

#ifndef INPUT_H
#define INPUT_H

typedef enum {
    INPUT_OK,
    INPUT_ERROR,
    INPUT_TOO_LONG
} inputResult;

inputResult readLine(char* buffer, size_t size);
int readChoice(int min, int max);

#endif
