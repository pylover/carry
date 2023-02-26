#include <cutest.h>
#include "fcarry.h"


void
test_fcarry_init() {
    int i;
    struct foo tmp;
    struct fcarry c;

    eqint(0, fcarry_init(&c));
    eqint(0, fcarry_count(&c));
    eqint(true, fcarry_isempty(&c));
    eqint(false, fcarry_isfull(&c));
    for (i = 0; i < CSIZE; i++) {
        eqint(-1, fcarry_copy(&c, &tmp, i));
    }
}


// void
// test_fcarry_append() {
//     char i;
//     struct fcarry c;
//     fcarry_init(&c);
//     
//     for (i = 0; i < CSIZE; i++) {
//         eqint(0, fcarry_appendp(&c, &i));
//     }
//     eqint(8, fcarry_count(&c));
//     eqint(-1, fcarry_appendp(&c, &i8));
//     eqint(8, fcarry_count(&c));
// }
// 
// 
// void
// test_fcarry_delete() {
//     char i;
//     struct fcarry c;
//     fcarry_init(&c);
//     
//     for (i = 0; i < CSIZE; i++) {
//         fcarry_appendp(&c, &i);
//     }
//     eqint(8, fcarry_count(&c));
//     eqint(0, *fcarry_getp(&c, 0));
//   
//     eqint(0, fcarry_delete(&c, 7));
//     eqint(7, fcarry_count(&c));
//     for (i = 0; i < 7; i++) {
//         eqint(i, *fcarry_getp(&c, i));
//     }
//     
//     int ctemp = 7;
//     int loop = 0;
//     while (fcarry_count(&c)) {
//         loop++;
//         eqint(ctemp--, fcarry_count(&c));
//         eqint(0, fcarry_delete(&c, 0));
//         eqint(ctemp, fcarry_count(&c));
//         for (i = 0; i < ctemp; i++) {
//             eqint(i + loop, *fcarry_getp(&c, i));
//         }
//         isnull(fcarry_getp(&c, i+1));
//     }
//     eqint(-1, fcarry_delete(&c, 0));
// }
// 
// 
// void
// test_fcarry_insert() {
//     struct fcarry c;
//     fcarry_init(&c);
// 
//     /* Insert on empty list */
//     eqint(0, fcarry_insertp(&c, 0, &i1));
//     eqint(1, *fcarry_getp(&c, 0));
//    
//     /* Insert on semi-full list */
//     fcarry_appendp(&c, &i2);
//     fcarry_appendp(&c, &i4);
//     eqint(0, fcarry_insertp(&c, 0, &i0));
//     eqint(0, *fcarry_getp(&c, 0));
//     eqint(1, *fcarry_getp(&c, 1));
//     eqint(2, *fcarry_getp(&c, 2));
//     eqint(4, *fcarry_getp(&c, 3));
// 
//     /* Insert at the middle of the list */
//     eqint(0, fcarry_insertp(&c, 3, &i3));
//     eqint(0, *fcarry_getp(&c, 0));
//     eqint(1, *fcarry_getp(&c, 1));
//     eqint(2, *fcarry_getp(&c, 2));
//     eqint(3, *fcarry_getp(&c, 3));
//     eqint(4, *fcarry_getp(&c, 4));
// 
//     /* Insert at the end of the list */
//     eqint(0, fcarry_insertp(&c, 5, &i5));
//     eqint(0, *fcarry_getp(&c, 0));
//     eqint(1, *fcarry_getp(&c, 1));
//     eqint(2, *fcarry_getp(&c, 2));
//     eqint(3, *fcarry_getp(&c, 3));
//     eqint(4, *fcarry_getp(&c, 4));
//     eqint(5, *fcarry_getp(&c, 5));
// 
//     /* Insert at invalid position */
//     eqint(-1, fcarry_insertp(&c, 7, &i8));
// }
