#include <stddef.h>
#include <string.h>


int
CFNAME(init)  (struct CSNAME *c) {
    memset(c->buffer, 0, sizeof(CTYPE) * CSIZE);
    c->count = 0;
    return 0;
}


bool
CFNAME(isfull) (struct CSNAME *c) {
    return c->count == CSIZE;
}


bool
CFNAME(isempty) (struct CSNAME *c) {
    return c->count == 0;
}


size_t
CFNAME(count) (struct CSNAME *c) {
    return c->count;
}


int
CFNAME(copy) (struct CSNAME *c, CTYPE *out, int index) {
    if (c->count <= index) {
        return -1;
    }
    
    memcpy(out, &(c->buffer[index]), sizeof(CTYPE));
    return 0;
}


CTYPE *
CFNAME(getp) (struct CSNAME *c, int index) {
    if (c->count <= index) {
        return NULL;
    }
    
    return &(c->buffer[index]);
}


int
CFNAME(appendp) (struct CSNAME *c, CTYPE *item) {
    int i;
    
    if (c->count == CSIZE) {
        /* full */
        return -1;
    }
    
    memcpy(&(c->buffer[c->count]), item, sizeof(CTYPE));
    c->count++;
    return 0;
}


int
CFNAME(insertp) (struct CSNAME *c, int index, CTYPE *item) {
    int i;
    
    if (c->count == CSIZE) {
        /* full */
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
CFNAME(delete) (struct CSNAME *c, int index) {
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
