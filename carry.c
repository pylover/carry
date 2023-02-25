#include <stddef.h>
#include <string.h>


enum carry_status
carry_init (struct carry *c) {
    memset(c->buffer, 0, sizeof(int) * CARRY_SIZE);
    c->count = 0;
    return CARRY_OK;
}


bool
carry_isfull(struct carry *c) {
    return c->count == CARRY_SIZE;
}


bool
carry_isempty(struct carry *c) {
    return c->count == 0;
}


enum carry_status
carry_count(struct carry *c) {
    return c->count;
}


enum carry_status
carry_copy(struct carry *c, int *out, int index) {
    if (c->count <= index) {
        return CARRY_INDEXERROR;
    }
    
    memcpy(out, &(c->buffer[index]), sizeof(int));
    return CARRY_OK;
}


int *
carry_getp(struct carry *c, int index) {
    if (c->count <= index) {
        return NULL;
    }
    
    return &(c->buffer[index]);
}


enum carry_status
carry_appendp(struct carry *c, int *item) {
    int i;
    
    if (carry_isfull(c)) {
        return CARRY_FULL;
    }
    
    memcpy(&(c->buffer[c->count]), item, sizeof(int));
    c->count++;
    return CARRY_OK;
}


enum carry_status
carry_insertp(struct carry *c, int index, int *item) {
    int i;
    
    if (carry_isfull(c)) {
        return CARRY_FULL;
    }
    
    if (c->count < index) {
        return CARRY_INDEXERROR;
    }
    
    c->count++;
    for (i = c->count; i >= index; i--) {
        memcpy(&(c->buffer[i]), &(c->buffer[i-1]), sizeof(int));
    }
    
    memcpy(&(c->buffer[index]), item, sizeof(int));
    return CARRY_OK;
}


enum carry_status
carry_delete(struct carry *c, int index) {
    int i;

    if (c->count <= index) {
        return CARRY_INDEXERROR;
    }

    for (i = (index + 1); i < c->count; i++) {
        memcpy(&(c->buffer[i-1]), &(c->buffer[i]), sizeof(int));
    }
    c->count--;
    return CARRY_OK;
}
