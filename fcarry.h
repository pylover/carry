#ifndef FCARRY_H
#define FCARRY_H


#undef CARRY_H
#undef CNAME
#undef CTYPE
#undef CSIZE


struct foo {
    int bar;
    int baz;
};


#define CNAME(name) f ## name
#define CTYPE struct foo
#define CSIZE 8
#include "carry.h"


#endif
