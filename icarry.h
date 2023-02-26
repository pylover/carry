#ifndef ICARRY_H
#define ICARRY_H


#undef CARRY_H
#undef CNAME
#undef CTYPE
#undef CSIZE


#define CNAME(name) i ## name
#define CTYPE int
#define CSIZE  8
#include "carry.h"


#endif
