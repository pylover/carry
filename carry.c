#include <stddef.h>
#include <string.h>


enum carry_status
carry_init (struct carry *c) {
    memset(c->buffer, 0, sizeof(int) * CARRY_SIZE);
    memset(c->items, 0, sizeof(void*) * CARRY_SIZE);
    c->count = 0;
    return CARRY_OK;
}


enum carry_status
carry_isfull(struct carry *c) {
    return c->count == CARRY_SIZE;
}


enum carry_status
carry_append(struct carry *c, int item) {
    int i;
    
    if (carry_isfull(c)) {
        return CARRY_FULL;
    }
    
    memcpy(&(c->buffer[c->count]), &item, sizeof(int));
    c->items[c->count] = &(c->buffer[c->count]);
    c->count++;
    return CARRY_OK;

    // for (i = 0; i < c->size; i++) {
    //     if (c->items[i]) {
    //         continue;
    //     }
    //     c->items[i] = &c->buffer[i];
    //     break;
    // }

    // return CARRY_OK;
}
