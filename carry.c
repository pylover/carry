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
#include <stdlib.h>  // NOLINT
#include <string.h>


int
CARRYNAME(init)(struct CARRYSELF() *self, size_t size) {
    self->pool = calloc(size, sizeof(CARRYTYPE*));
    if (self->pool == NULL) {
        return -1;
    }
    memset(self->pool, 0, size * sizeof(CARRYTYPE*));
    self->count = 0;
    self->size = size;
    return 0;
}


void
CARRYNAME(deinit)(struct CARRYSELF() *self) {
    if (self->pool == NULL) {
        return;
    }
    free(self->pool);
}


int
CARRYNAME(append)(struct CARRYSELF() *self, CARRYTYPE *item) {
    int i;

    if (item == NULL) {
        return -1;
    }

    if (CARRY_ISFULL(self)) {
        return -1;
    }

    for (i = 0; i < self->size; i++) {
        if (self->pool[i] == NULL) {
            goto found;
        }
    }

notfound:
    return -1;

found:
    self->pool[i] = item;
    self->count++;
    return i;
}


int
CARRYNAME(vacuumflag)(struct CARRYSELF() *self, unsigned int index) {
    if (self->size <= index) {
        return -1;
    }

    self->pool[index] = NULL;
    return 0;
}


CARRYTYPE*
CARRYNAME(get)(struct CARRYSELF() *self, unsigned int index) {
    if (self->size <= index) {
        return NULL;
    }

    return self->pool[index];
}


void
CARRYNAME(vacuum)(struct CARRYSELF() *self, CARRYNAME(vacuumcb) cb) {
    int i;
    int shift = 0;

    for (i = 0; i < self->count; i++) {
        if (self->pool[i] == NULL) {
            shift++;
            continue;
        }

        if (!shift) {
            continue;
        }

        self->pool[i - shift] = self->pool[i];
        self->pool[i] = NULL;
        if (cb) {
            cb(self->pool[i - shift], i - shift);
        }
    }

    self->count -= shift;
}
