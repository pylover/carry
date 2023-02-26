#include <stddef.h>
#include <string.h>


int
CNAME(carry_init)  (struct CNAME(carry) *c) {
    memset(c->buffer, 0, sizeof(CTYPE) * CSIZE);
    c->count = 0;
    return 0;
}


bool
CNAME(carry_isfull) (struct CNAME(carry) *c) {
    return c->count == CSIZE;
}


bool
CNAME(carry_isempty) (struct CNAME(carry) *c) {
    return c->count == 0;
}


size_t
CNAME(carry_count) (struct CNAME(carry) *c) {
    return c->count;
}


int
CNAME(carry_copy) (struct CNAME(carry) *c, CTYPE *out, int index) {
    if (c->count <= index) {
        return -1;
    }
    
    memcpy(out, &(c->buffer[index]), sizeof(CTYPE));
    return 0;
}


CTYPE *
CNAME(carry_getp) (struct CNAME(carry) *c, int index) {
    if (c->count <= index) {
        return NULL;
    }
    
    return &(c->buffer[index]);
}


int
CNAME(carry_appendp) (struct CNAME(carry) *c, CTYPE *item) {
    int i;
    
    if (CNAME(carry_isfull)(c)) {
        return -1;
    }
    
    memcpy(&(c->buffer[c->count]), item, sizeof(CTYPE));
    c->count++;
    return 0;
}


int
CNAME(carry_insertp) (struct CNAME(carry) *c, int index, CTYPE *item) {
    int i;
    
    if (CNAME(carry_isfull)(c)) {
        return -1;
    }
    
    if (c->count < index) {
        return -1;
    }
    
    c->count++;
    for (i = c->count; i >= index; i--) {
        memcpy(&(c->buffer[i]), &(c->buffer[i-1]), sizeof(CTYPE));
    }
    
    memcpy(&(c->buffer[index]), item, sizeof(CTYPE));
    return 0;
}


int
CNAME(carry_delete) (struct CNAME(carry) *c, int index) {
    int i;

    if (c->count <= index) {
        return -1;
    }

    for (i = (index + 1); i < c->count; i++) {
        memcpy(&(c->buffer[i-1]), &(c->buffer[i]), sizeof(CTYPE));
    }
    c->count--;
    return 0;
}
