#include <clog.h>
#include <cutest.h>
#include <unistd.h>
#include <fcntl.h>

#include "carry_int.h"


void
test_carry_init() {
    int i;
    int tmp;
    struct carry c;

    eqint(CARRY_OK, carry_init(&c));
    eqint(0, carry_count(&c));
    eqint(true, carry_isempty(&c));
    eqint(false, carry_isfull(&c));
    for (i = 0; i < CARRY_SIZE; i++) {
        eqint(CARRY_INDEXERROR, carry_copy(&c, &tmp, i));
    }
}


static int i0 = 0;
static int i1 = 1;
static int i2 = 2;
static int i3 = 3;
static int i4 = 4;
static int i5 = 5;
static int i6 = 6;
static int i7 = 7;
static int i8 = 8;
static int i9 = 9;


void
test_carry_append() {
    int i;
    struct carry c;
    carry_init(&c);
    
    for (i = 0; i < CARRY_SIZE; i++) {
        eqint(CARRY_OK, carry_appendp(&c, &i));
    }
    eqint(8, carry_count(&c));
    eqint(CARRY_FULL, carry_appendp(&c, &i8));
    eqint(8, carry_count(&c));
}


void
test_carry_delete() {
    int i;
    struct carry c;
    carry_init(&c);
    
    for (i = 0; i < CARRY_SIZE; i++) {
        carry_appendp(&c, &i);
    }
    eqint(8, carry_count(&c));
    eqint(0, *carry_getp(&c, 0));
  
    eqint(CARRY_OK, carry_delete(&c, 7));
    eqint(7, carry_count(&c));
    for (i = 0; i < 7; i++) {
        eqint(i, *carry_getp(&c, i));
    }
    
    int ctemp = 7;
    int loop = 0;
    while (carry_count(&c)) {
        loop++;
        eqint(ctemp--, carry_count(&c));
        eqint(CARRY_OK, carry_delete(&c, 0));
        eqint(ctemp, carry_count(&c));
        for (i = 0; i < ctemp; i++) {
            eqint(i + loop, *carry_getp(&c, i));
        }
        isnull(carry_getp(&c, i+1));
    }
    eqint(CARRY_INDEXERROR, carry_delete(&c, 0));
}


void
test_carry_insert() {
    struct carry c;
    carry_init(&c);

    /* Insert on empty list */
    eqint(CARRY_OK, carry_insertp(&c, 0, &i1));
    eqint(1, *carry_getp(&c, 0));
   
    /* Insert on semi-full list */
    carry_appendp(&c, &i2);
    carry_appendp(&c, &i4);
    eqint(CARRY_OK, carry_insertp(&c, 0, &i0));
    eqint(0, *carry_getp(&c, 0));
    eqint(1, *carry_getp(&c, 1));
    eqint(2, *carry_getp(&c, 2));
    eqint(4, *carry_getp(&c, 3));

    /* Insert at the middle of the list */
    eqint(CARRY_OK, carry_insertp(&c, 3, &i3));
    eqint(0, *carry_getp(&c, 0));
    eqint(1, *carry_getp(&c, 1));
    eqint(2, *carry_getp(&c, 2));
    eqint(3, *carry_getp(&c, 3));
    eqint(4, *carry_getp(&c, 4));

    /* Insert at the end of the list */
    eqint(CARRY_OK, carry_insertp(&c, 5, &i5));
    eqint(0, *carry_getp(&c, 0));
    eqint(1, *carry_getp(&c, 1));
    eqint(2, *carry_getp(&c, 2));
    eqint(3, *carry_getp(&c, 3));
    eqint(4, *carry_getp(&c, 4));
    eqint(5, *carry_getp(&c, 5));

    /* Insert at invalid position */
    eqint(CARRY_INDEXERROR, carry_insertp(&c, 7, &i8));
}


int main() {
    test_carry_init();
    test_carry_append();
    test_carry_delete();
    test_carry_insert();
    return EXIT_SUCCESS;
}
