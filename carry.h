#include <stddef.h>
#include <stdbool.h>

/* Generic stuff */
#define CARRY_NAME_PASTER(x, y) x ## _ ## y
#define CARRY_NAME_EVALUATOR(x, y)  CARRY_NAME_PASTER(x, y)
#define CARRY_NAME(n) CARRY_NAME_EVALUATOR(CARRY_TYPE, n)


struct
CARRY_NAME(array) {
    CARRY_TYPE *array;
    size_t size;
    size_t count;
};


int
CARRY_NAME(array_init)(struct CARRY_NAME(array) *self, size_t size);


int
CARRY_NAME(array_append)(struct CARRY_NAME(array) *self, CARRY_TYPE item);


// int
// CFNAME(copy)(struct CSNAME *c, CTYPE *out, int index);
//
//
// CTYPE *
// CFNAME(getp) (struct CSNAME *c, int index);
//
//
// int
// CFNAME(appendp) (struct CSNAME *c, CTYPE *item);
//
//
// int
// CFNAME(insertp) (struct CSNAME *c, int index, CTYPE *item);
//
//
// int
// CFNAME(delete) (struct CSNAME *c, int index);
//
//
// bool
// CFNAME(isfull) (struct CSNAME *c);
//
//
// bool
// CFNAME(isempty) (struct CSNAME *c);
//
//
// size_t
// CFNAME(count) (struct CSNAME *c);
