#ifndef CARRY_H
#define CARRY_H


#include <stddef.h>
#include <stdbool.h>


enum 
carry_status {
    CARRY_OK,
    CARRY_EMPTY,
    CARRY_FULL,
    CARRY_INDEXERROR,
};


struct 
carry {
    int buffer[CARRY_SIZE];
    size_t count;
};


enum carry_status
carry_init(struct carry *c);


enum carry_status
carry_copy(struct carry *c, int *out, int index);


int *
carry_getp(struct carry *c, int index);


enum carry_status
carry_appendp(struct carry *c, int *item);


enum carry_status
carry_insertp(struct carry *c, int index, int *item);


enum carry_status
carry_delete(struct carry *c, int index);


bool
carry_isfull(struct carry *c);


bool
carry_isempty(struct carry *c);


enum carry_status
carry_count(struct carry *c);


#endif
