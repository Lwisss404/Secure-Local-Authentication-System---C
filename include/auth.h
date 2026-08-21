#ifndef AUTH_H
#define AUTH_H

typedef enum {
    AUTH_SUCCESS,
    AUTH_CANCELLED,
    AUTH_FAILURE
} authResult;

authResult registerUser(void);
authResult loginUser(void);

#endif
