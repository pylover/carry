# carry

C generic fixed-length array management.


## How to use

Suppose you need an array for type `foo`:


```c
/* fcarry.h */
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


#endif
```

```c
/* fcarry.c */
#include "fcarry.h"
#include "carry.c"
```

Now, include and use it:

```c
#include "fcarry.h"


struct foo tmp;
struct fcarry c;


finit(&c);
fcount(&c);
fisempty(&c);
fisfull(&c);
fcopy(&c, &tmp, i);
```

## Running tests

Install https://github.com/pylover/cutest.


```bash
make clean test
```
