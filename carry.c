#include <stddef.h>
#include <string.h>


enum carry_status
CNAME(carry_init)  (struct CNAME(carry) *c) {
    memset(c->buffer, 0, sizeof(CTYPE) * CSIZE);
    c->count = 0;
    return CARRY_OK;
}


bool
CNAME(carry_isfull) (struct CNAME(carry) *c) {
    return c->count == CSIZE;
}


bool
CNAME(carry_isempty) (struct CNAME(carry) *c) {
    return c->count == 0;
}


enum carry_status
CNAME(carry_count) (struct CNAME(carry) *c) {
    return c->count;
}


enum carry_status
CNAME(carry_copy) (struct CNAME(carry) *c, CTYPE *out, int index) {
    if (c->count <= index) {
        return CARRY_INDEXERROR;
    }
    
    memcpy(out, &(c->buffer[index]), sizeof(CTYPE));
    return CARRY_OK;
}


CTYPE *
CNAME(carry_getp) (struct CNAME(carry) *c, int index) {
    if (c->count <= index) {
        return NULL;
    }
    
    return &(c->buffer[index]);
}


enum carry_status
CNAME(carry_appendp) (struct CNAME(carry) *c, CTYPE *item) {
    int i;
    
    if (carry_isfull(c)) {
        return CARRY_FULL;
    }
    
    memcpy(&(c->buffer[c->count]), item, sizeof(CTYPE));
    c->count++;
    return CARRY_OK;
}


enum carry_status
CNAME(carry_insertp) (struct CNAME(carry) *c, int index, CTYPE *item) {
    int i;
    
    if (carry_isfull(c)) {
        return CARRY_FULL;
    }
    
    if (c->count < index) {
        return CARRY_INDEXERROR;
    }
    
    c->count++;
    for (i = c->count; i >= index; i--) {
        memcpy(&(c->buffer[i]), &(c->buffer[i-1]), sizeof(CTYPE));
    }
    
    memcpy(&(c->buffer[index]), item, sizeof(CTYPE));
    return CARRY_OK;
}


enum carry_status
CNAME(carry_delete) (struct CNAME(carry) *c, int index) {
    int i;

    if (c->count <= index) {
        return CARRY_INDEXERROR;
    }

    for (i = (index + 1); i < c->count; i++) {
        memcpy(&(c->buffer[i-1]), &(c->buffer[i]), sizeof(CTYPE));
    }
    c->count--;
    return CARRY_OK;
}
