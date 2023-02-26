#ifndef CARRY_H
#define CARRY_H


#include <stddef.h>
#include <stdbool.h>


struct 
CSNAME {
    CTYPE buffer[CSIZE];
    size_t count;
};


int
CFNAME(init)(struct CSNAME *c);


int
CFNAME(copy)(struct CSNAME *c, CTYPE *out, int index);


CTYPE *
CFNAME(getp) (struct CSNAME *c, int index);


int
CFNAME(appendp) (struct CSNAME *c, CTYPE *item);


int
CFNAME(insertp) (struct CSNAME *c, int index, CTYPE *item);


int
CFNAME(delete) (struct CSNAME *c, int index);


bool
CFNAME(isfull) (struct CSNAME *c);


bool
CFNAME(isempty) (struct CSNAME *c);


size_t
CFNAME(count) (struct CSNAME *c);


#endif
