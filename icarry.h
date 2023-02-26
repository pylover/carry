#ifndef ICARRY_H
#define ICARRY_H


#undef CARRY_H
#undef CSNAME
#undef CFNAME
#undef CTYPE
#undef CSIZE


#define CSNAME ints
#define CFNAME(name) i ## name
#define CTYPE int
#define CSIZE 8
#include "carry.h"


#endif
