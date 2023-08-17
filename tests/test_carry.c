#include <cutest.h>


typedef int* intptr;


#undef CARRY_ISEMPTY
#define CARRY_ISEMPTY(c) (c == NULL)
#undef CARRY_TYPE
#define CARRY_TYPE intptr
#include "carry.h"
#include "carry.c"


void
test_carry() {
    int index;
    struct intptr_array arr;
    intptr_array_init(&arr, 4);

    eqint(4, arr.size);
    eqint(0, arr.count);

    int foo = 1;
    int bar = 2;
    int baz = 3;
    int qux = 4;

    index = intptr_array_append(&arr, &foo);
    eqint(1, arr.count);
    eqint(0, index);

    index = intptr_array_append(&arr, &bar);
    eqint(2, arr.count);
    eqint(1, index);

    eqint(0, intptr_array_set(&arr, &baz, 2));
    eqint(3, arr.count);

    eqint(0, intptr_array_set(&arr, &baz, 2));
    eqint(3, arr.count);

    index = intptr_array_append(&arr, &qux);
    eqint(4, arr.count);
    eqint(3, index);

    eqint(0, intptr_array_set(&arr, NULL, 2));
    eqint(3, arr.count);

    eqint(-1, intptr_array_set(&arr, NULL, 4));
    eqint(3, arr.count);
}


void
main() {
    test_carry();
}
