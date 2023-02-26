#ifndef FCARRY_H
#define FCARRY_H


// Undef for previous definitions
#undef CARRY_H
#undef CSNAME
#undef CFNAME
#undef CTYPE
#undef CSIZE


struct foo {
    int bar;
    int baz;
};


// Name of the struct
#define CSNAME foos

// Function name
#define CFNAME(name) f ## name

// Type variable
#define CTYPE struct foo

// Size of packet
#define CSIZE 8

// Then import
#include "carry.h"


#endif
