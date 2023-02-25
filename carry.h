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
CNAME(carry) {
    CTYPE buffer[CSIZE];
    size_t count;
};


enum carry_status
CNAME(carry_init)(struct CNAME(carry) *c);


enum carry_status
CNAME(carry_copy)(struct CNAME(carry) *c, CTYPE *out, int index);


CTYPE *
CNAME(carry_getp) (struct CNAME(carry) *c, int index);


enum carry_status
CNAME(carry_appendp) (struct CNAME(carry) *c, CTYPE *item);


enum carry_status
CNAME(carry_insertp) (struct CNAME(carry) *c, int index, CTYPE *item);


enum carry_status
CNAME(carry_delete) (struct CNAME(carry) *c, int index);


bool
CNAME(carry_isfull) (struct CNAME(carry) *c);


bool
CNAME(carry_isempty) (struct CNAME(carry) *c);


enum carry_status
CNAME(carry_count) (struct CNAME(carry) *c);


#endif
