# carry

C generic fixed-length array management.


## How to use

Suppose you need an array for type `foo`:


```c
/* fcarry.h */
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
```

```c
/* fcarry.c */
#include "fcarry.h"
#include "carry.c"
```

Now, include and use it:

```c
struct foo tmp;
struct fcarry c;

fcarry_init(&c);
fcarry_count(&c);
fcarry_isempty(&c);
fcarry_isfull(&c);
fcarry_copy(&c, &tmp, i);
```

## Running tests

Install https://github.com/pylover/cutest.


```bash
make clean test
```
