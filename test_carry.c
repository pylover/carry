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
    test_icarry_init();
    test_icarry_append();
    test_icarry_delete();
    test_icarry_insert();

    // Defined in test_fcarry.c
    test_fcarry_init();
    test_fcarry_append();
    test_fcarry_delete();
    // test_fcarry_insert();
    return EXIT_SUCCESS;
}
