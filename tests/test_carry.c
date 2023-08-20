// Copyright 2023 Vahid Mardani
/*
 * This file is part of carry.
 *  carry is free software: you can redistribute it and/or modify it under
 *  the terms of the GNU General Public License as published by the Free
 *  Software Foundation, either version 3 of the License, or (at your option)
 *  any later version.
 *
 *  carry is distributed in the hope that it will be useful, but WITHOUT ANY
 *  WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 *  FOR A PARTICULAR PURPOSE. See the GNU General Public License for more
 *  details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with carry. If not, see <https://www.gnu.org/licenses/>.
 *
 *  Author: Vahid Mardani <vahid.mardani@gmail.com>
 */
#include <cutest.h>


#undef CARRYTYPE
#define CARRYTYPE int
#include "carry.h"
#include "carry.c"


void
test_generic_pool() {
    int index;
    struct int_pool pool;
    int_pool_init(&pool, 4);

    eqint(4, pool.size);
    eqint(0, pool.count);

    int foo = 1;
    int bar = 2;
    int baz = 3;
    int qux = 4;

    index = int_pool_append(&pool, &foo);
    eqint(1, pool.count);
    eqint(0, index);

    index = int_pool_append(&pool, &bar);
    eqint(2, pool.count);
    eqint(1, index);

    index = int_pool_append(&pool, &baz);
    eqint(3, pool.count);
    eqint(2, index);

    eqptr(&foo, int_pool_get(&pool, 0));
    eqptr(&bar, int_pool_get(&pool, 1));
    eqptr(&baz, int_pool_get(&pool, 2));
    eqptr(NULL, int_pool_get(&pool, 3));

    int_pool_deinit(&pool);
}


struct itemindex {
    int *item;
    unsigned int index;
};


static struct itemindex itemindexes[8];
static int itemindex_count = 0;
static int vacuum_callback_count = 0;


static void
_vacuum_callback(int *item, unsigned int newindex) {
    struct itemindex *itemindex = &itemindexes[itemindex_count++];
    itemindex->item = item;
    itemindex->index = newindex;
    vacuum_callback_count++;
}


static void
eqitemindex(int *item, unsigned int index, struct itemindex *itemindex) {
    eqptr(item, itemindex->item);
    eqint(index, itemindex->index);
}


void
test_generic_pool_vacuum() {
    struct int_pool pool;

    int foo = 1;
    int bar = 2;
    int baz = 3;
    int qux = 4;
    int quux = 5;

    /* When first element is empty */
    vacuum_callback_count = 0;
    itemindex_count = 0;
    int_pool_init(&pool, 8);
    int_pool_append(&pool, &quux);
    int_pool_append(&pool, &foo);
    int_pool_append(&pool, &bar);
    int_pool_append(&pool, &quux);
    int_pool_append(&pool, &quux);
    int_pool_append(&pool, &baz);
    int_pool_append(&pool, &qux);

    /* Set some elements to null */
    int_pool_vacuumflag(&pool, 0);
    int_pool_vacuumflag(&pool, 3);
    int_pool_vacuumflag(&pool, 4);

    /* Do action! */
    int_pool_vacuum(&pool, _vacuum_callback);

    /* Check new indexes */
    eqitemindex(&foo, 0, &itemindexes[0]);
    eqitemindex(&bar, 1, &itemindexes[1]);
    eqitemindex(&baz, 2, &itemindexes[2]);
    eqitemindex(&qux, 3, &itemindexes[3]);
    eqint(4, vacuum_callback_count);

    /* Check collection */
    eqptr(&foo, int_pool_get(&pool, 0));
    eqptr(&bar, int_pool_get(&pool, 1));
    eqptr(&baz, int_pool_get(&pool, 2));
    eqptr(&qux, int_pool_get(&pool, 3));
    isnull(int_pool_get(&pool, 4));
    isnull(int_pool_get(&pool, 5));
    isnull(int_pool_get(&pool, 6));
    isnull(int_pool_get(&pool, 7));
    eqint(4, pool.count);

    int_pool_deinit(&pool);

    /* When first element is not empty */
    vacuum_callback_count = 0;
    itemindex_count = 0;
    int_pool_init(&pool, 8);
    int_pool_append(&pool, &foo);
    int_pool_append(&pool, &quux);
    int_pool_append(&pool, &bar);
    int_pool_append(&pool, &quux);
    int_pool_append(&pool, &quux);
    int_pool_append(&pool, &baz);
    int_pool_append(&pool, &qux);
    int_pool_append(&pool, &quux);

    /* Set some elements to null */
    int_pool_vacuumflag(&pool, 1);
    int_pool_vacuumflag(&pool, 3);
    int_pool_vacuumflag(&pool, 4);

    /* Do action! */
    int_pool_vacuum(&pool, _vacuum_callback);

    /* Check new indexes */
    eqitemindex(&bar, 1, &itemindexes[0]);
    eqitemindex(&baz, 2, &itemindexes[1]);
    eqitemindex(&qux, 3, &itemindexes[2]);
    eqitemindex(&quux, 4, &itemindexes[3]);
    eqint(4, vacuum_callback_count);

    /* Check collection */
    eqptr(&foo, int_pool_get(&pool, 0));
    eqptr(&bar, int_pool_get(&pool, 1));
    eqptr(&baz, int_pool_get(&pool, 2));
    eqptr(&qux, int_pool_get(&pool, 3));
    eqptr(&quux, int_pool_get(&pool, 4));
    isnull(int_pool_get(&pool, 5));
    isnull(int_pool_get(&pool, 6));
    isnull(int_pool_get(&pool, 7));

    int_pool_deinit(&pool);
}


void
main() {
    test_generic_pool();
    test_generic_pool_vacuum();
}
