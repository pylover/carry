#ifndef CARRY_H
#define CARRY_H


#define GNAME(name) name


enum 
carry_status {
    CARRY_OK,
    CARRY_EMPTY,
    CARRY_FULL,
    CARRY_BADARG,
};


struct 
GNAME(carry) {
    T buffer[CARRY_SIZE];
    void *items[CARRY_SIZE];
    size_t size;
};


#endif
