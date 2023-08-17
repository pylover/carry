#include <stddef.h>
#include <string.h>


int
CARRY_NAME(array_init)(struct CARRY_NAME(array) *self, size_t size) {
    self->array = calloc(size, sizeof(CARRY_TYPE));
    memset(self->array, 0, size * sizeof(CARRY_TYPE));
    self->count = 0;
    self->size = size;
    return 0;
}


int
CARRY_NAME(array_append)(struct CARRY_NAME(array) *self, CARRY_TYPE item) {
    int i;

    for (i = 0; i < self->size; i++) {
        if (CARRY_ISEMPTY(self->array[i])) {
            goto found;
        }
    }

notfound:
    return -1;

found:
    self->array[i] = item;
    self->count++;
    return i;
}


int
CARRY_NAME(array_set)(struct CARRY_NAME(array) *self, CARRY_TYPE item,
        unsigned int index) {
    if (self->size <= index) {
        return -1;
    }

    if (CARRY_ISEMPTY(item)) {
        if (!CARRY_ISEMPTY(self->array[index])) {
            self->count--;
        }
    }
    else {
        if (CARRY_ISEMPTY(self->array[index])) {
            self->count++;
        }
    }

    self->array[index] = item;
    return 0;
}
// bool
// CFNAME(isfull) (struct CSNAME *c) {
//     return c->count == CSIZE;
// }
//
//
// bool
// CFNAME(isempty) (struct CSNAME *c) {
//     return c->count == 0;
// }
//
//
// size_t
// CFNAME(count) (struct CSNAME *c) {
//     return c->count;
// }
//
//
// int
// CFNAME(copy) (struct CSNAME *c, CTYPE *out, int index) {
//     if (c->count <= index) {
//         return -1;
//     }
//
//     memcpy(out, &(c->buffer[index]), sizeof(CTYPE));
//     return 0;
// }
//
//
// CTYPE *
// CFNAME(getp) (struct CSNAME *c, int index) {
//     if (c->count <= index) {
//         return NULL;
//     }
//
//     return &(c->buffer[index]);
// }
//
//
// int
// CFNAME(appendp) (struct CSNAME *c, CTYPE *item) {
//     int i;
//
//     if (c->count == CSIZE) {
//         /* full */
//         return -1;
//     }
//
//     memcpy(&(c->buffer[c->count]), item, sizeof(CTYPE));
//     c->count++;
//     return 0;
// }
//
//
// int
// CFNAME(insertp) (struct CSNAME *c, int index, CTYPE *item) {
//     int i;
//
//     if (c->count == CSIZE) {
//         /* full */
//         return -1;
//     }
//
//     if (c->count < index) {
//         return -1;
//     }
//
//     c->count++;
//     for (i = c->count; i >= index; i--) {
//         memcpy(&(c->buffer[i]), &(c->buffer[i-1]), sizeof(CTYPE));
//     }
//
//     memcpy(&(c->buffer[index]), item, sizeof(CTYPE));
//     return 0;
// }
//
//
// int
// CFNAME(delete) (struct CSNAME *c, int index) {
//     int i;
//
//     if (c->count <= index) {
//         return -1;
//     }
//
//     for (i = (index + 1); i < c->count; i++) {
//         memcpy(&(c->buffer[i-1]), &(c->buffer[i]), sizeof(CTYPE));
//     }
//     c->count--;
//     return 0;
// }
