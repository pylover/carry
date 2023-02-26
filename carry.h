#ifndef CARRY_H
#define CARRY_H


#include <stddef.h>
#include <stdbool.h>


struct 
CNAME(carry) {
    CTYPE buffer[CSIZE];
    size_t count;
};


int
CNAME(carry_init)(struct CNAME(carry) *c);


int
CNAME(carry_copy)(struct CNAME(carry) *c, CTYPE *out, int index);


CTYPE *
CNAME(carry_getp) (struct CNAME(carry) *c, int index);


int
CNAME(carry_appendp) (struct CNAME(carry) *c, CTYPE *item);


int
CNAME(carry_insertp) (struct CNAME(carry) *c, int index, CTYPE *item);


int
CNAME(carry_delete) (struct CNAME(carry) *c, int index);


bool
CNAME(carry_isfull) (struct CNAME(carry) *c);


bool
CNAME(carry_isempty) (struct CNAME(carry) *c);


size_t
CNAME(carry_count) (struct CNAME(carry) *c);


#endif
