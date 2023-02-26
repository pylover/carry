#include <cutest.h>
#include "icarry.h"


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
test_icarry_init() {
    int i;
    int tmp;
    struct icarry c;

    eqint(0, icarry_init(&c));
    eqint(0, icarry_count(&c));
    eqint(true, icarry_isempty(&c));
    eqint(false, icarry_isfull(&c));
    for (i = 0; i < CSIZE; i++) {
        eqint(-1, icarry_copy(&c, &tmp, i));
    }
}


void
test_icarry_append() {
    int i;
    struct icarry c;
    icarry_init(&c);
    
    for (i = 0; i < CSIZE; i++) {
        eqint(0, icarry_appendp(&c, &i));
    }
    eqint(8, icarry_count(&c));
    eqint(-1, icarry_appendp(&c, &i8));
    eqint(8, icarry_count(&c));
}


void
test_icarry_delete() {
    int i;
    struct icarry c;
    icarry_init(&c);
    
    for (i = 0; i < CSIZE; i++) {
        icarry_appendp(&c, &i);
    }
    eqint(8, icarry_count(&c));
    eqint(0, *icarry_getp(&c, 0));
  
    eqint(0, icarry_delete(&c, 7));
    eqint(7, icarry_count(&c));
    for (i = 0; i < 7; i++) {
        eqint(i, *icarry_getp(&c, i));
    }
    
    int ctemp = 7;
    int loop = 0;
    while (icarry_count(&c)) {
        loop++;
        eqint(ctemp--, icarry_count(&c));
        eqint(0, icarry_delete(&c, 0));
        eqint(ctemp, icarry_count(&c));
        for (i = 0; i < ctemp; i++) {
            eqint(i + loop, *icarry_getp(&c, i));
        }
        isnull(icarry_getp(&c, i+1));
    }
    eqint(-1, icarry_delete(&c, 0));
}


void
test_icarry_insert() {
    struct icarry c;
    icarry_init(&c);

    /* Insert on empty list */
    eqint(0, icarry_insertp(&c, 0, &i1));
    eqint(1, *icarry_getp(&c, 0));
   
    /* Insert on semi-full list */
    icarry_appendp(&c, &i2);
    icarry_appendp(&c, &i4);
    eqint(0, icarry_insertp(&c, 0, &i0));
    eqint(0, *icarry_getp(&c, 0));
    eqint(1, *icarry_getp(&c, 1));
    eqint(2, *icarry_getp(&c, 2));
    eqint(4, *icarry_getp(&c, 3));

    /* Insert at the middle of the list */
    eqint(0, icarry_insertp(&c, 3, &i3));
    eqint(0, *icarry_getp(&c, 0));
    eqint(1, *icarry_getp(&c, 1));
    eqint(2, *icarry_getp(&c, 2));
    eqint(3, *icarry_getp(&c, 3));
    eqint(4, *icarry_getp(&c, 4));

    /* Insert at the end of the list */
    eqint(0, icarry_insertp(&c, 5, &i5));
    eqint(0, *icarry_getp(&c, 0));
    eqint(1, *icarry_getp(&c, 1));
    eqint(2, *icarry_getp(&c, 2));
    eqint(3, *icarry_getp(&c, 3));
    eqint(4, *icarry_getp(&c, 4));
    eqint(5, *icarry_getp(&c, 5));

    /* Insert at invalid position */
    eqint(-1, icarry_insertp(&c, 7, &i8));
}
