#ifndef ERR_DEF_H
#define ERR_DEF_H

typedef enum Err_T {
    ERR_OK = 0,
    ERR_INVALID_PARAM = -1,
    ERR_TIMEOUT = -2,
    ERR_UNKNOWN = -3
} Err_T;

#endif // ERR_DEF_H