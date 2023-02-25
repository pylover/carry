#include <clog.h>
#include <cutest.h>
#include <unistd.h>
#include <fcntl.h>

#include "carry_int.h"


void
test_carry_init() {
    struct carry c;
    eqint(CARRY_OK, carry_init(&c));

    eqint(CARRY_OK, carry_append(&c, 1));
}


int main() {
    test_carry_init();
    return EXIT_SUCCESS;
}
