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
        eqint(CARRY_INDEXERROR, carry_get(&c, &tmp, i));
    }
}


void
test_carry_append() {
    int i;
    struct carry c;
    carry_init(&c);
    
    for (i = 0; i < CARRY_SIZE; i++) {
        eqint(CARRY_OK, carry_append(&c, i));
    }
    eqint(8, carry_count(&c));
    eqint(CARRY_FULL, carry_append(&c, 8));
    eqint(8, carry_count(&c));
}


void
test_carry_delete() {
    int i;
    struct carry c;
    carry_init(&c);
    
    for (i = 0; i < CARRY_SIZE; i++) {
        carry_append(&c, i);
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


int main() {
    test_carry_init();
    test_carry_append();
    test_carry_delete();
    return EXIT_SUCCESS;
}
