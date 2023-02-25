#ifndef CARRY_H
#define CARRY_H


#include <stddef.h>


enum 
carry_status {
    CARRY_OK,
    CARRY_EMPTY,
    CARRY_FULL,
    CARRY_BADARG,
};


struct 
carry {
    int buffer[CARRY_SIZE];
    void *items[CARRY_SIZE];
    size_t size;
};


#endif
