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
    int *items[CARRY_SIZE];
    size_t count;
};


enum carry_status
carry_init (struct carry *c);


enum carry_status
carry_append(struct carry *c, int item);


enum carry_status
carry_isfull(struct carry *c);


#endif
