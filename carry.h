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
#include <stddef.h>
#include <stdbool.h>


#ifndef CARRY_H_
#define CARRY_H_
#define CARRY_ISFULL(self) ((self)->count == (self)->size)
#define CARRY_ISEMPTY(self) ((self)->count == 0)
#endif  // CARRY_H_


/* Generic stuff */
#define CARRYNAME_PASTER(x, y, z) x ## y ## z
#define CARRYNAME_EVALUATOR(x, y, z)  CARRYNAME_PASTER(x, y, z)
#define CARRYNAME(n) CARRYNAME_EVALUATOR(CARRYTYPE, _pool_, n)
#define CARRYSELF() CARRYNAME_EVALUATOR(CARRYTYPE, _, pool)


struct
CARRYSELF() {
    CARRYTYPE **pool;
    size_t size;
    size_t count;
};


typedef void (*CARRYNAME(vacuumcb)) (CARRYTYPE *item, unsigned int index);


int
CARRYNAME(init)(struct CARRYSELF() *self, size_t size);


void
CARRYNAME(deinit)(struct CARRYSELF() *self);


int
CARRYNAME(append)(struct CARRYSELF() *self, CARRYTYPE *item);


int
CARRYNAME(vacuumflag)(struct CARRYSELF() *self, unsigned int index);


CARRYTYPE*
CARRYNAME(get)(struct CARRYSELF() *self, unsigned int index);


void
CARRYNAME(vacuum)(struct CARRYSELF() *self, CARRYNAME(vacuumcb) cb);
