#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <cutest.h>

#include "icarry.h"
#include "fcarry.h"
#include "test_icarry.c"
#include "test_fcarry.c"


int main() {
    // Defined in test_icarry.c
    test_iinit();
    test_iappend();
    test_idelete();
    test_iinsert();

    // Defined in test_fcarry.c
    test_finit();
    test_fappend();
    test_fdelete();
    // test_fcarry_insert();
    return EXIT_SUCCESS;
}
