static struct foo f0 = {0, 10};
static struct foo f1 = {1, 11};
static struct foo f2 = {2, 12};
static struct foo f3 = {3, 13};
static struct foo f4 = {4, 14};
static struct foo f5 = {5, 15};
static struct foo f6 = {6, 16};
static struct foo f7 = {7, 17};
static struct foo f8 = {8, 18};
static struct foo f9 = {9, 19};


static struct foo *foos[10] = {
    &f0,
    &f1,
    &f2,
    &f3,
    &f4,
    &f5,
    &f6,
    &f7,
    &f8,
    &f9,
};


void
test_fcarry_init() {
    int i;
    struct foo tmp;
    struct fcarry c;

    eqint(0, fcarry_init(&c));
    eqint(0, fcarry_count(&c));
    eqint(true, fcarry_isempty(&c));
    eqint(false, fcarry_isfull(&c));
    for (i = 0; i < CSIZE; i++) {
        eqint(-1, fcarry_copy(&c, &tmp, i));
    }
}


void
test_fcarry_append() {
    char i;
    struct fcarry c;
    fcarry_init(&c);
    
    for (i = 0; i < CSIZE; i++) {
        eqint(0, fcarry_appendp(&c, foos[i]));
    }
    eqint(8, fcarry_count(&c));
    eqint(-1, fcarry_appendp(&c, &f8));
    eqint(8, fcarry_count(&c));
}


void
test_fcarry_delete() {
    char i;
    struct fcarry c;
    fcarry_init(&c);
    
    for (i = 0; i < CSIZE; i++) {
        fcarry_appendp(&c, foos[i]);
    }
    eqint(8, fcarry_count(&c));
    eqint(0, fcarry_getp(&c, 0)->bar);
  
    eqint(0, fcarry_delete(&c, 7));
    eqint(7, fcarry_count(&c));
    for (i = 0; i < 7; i++) {
        eqint(i, fcarry_getp(&c, i)->bar);
    }
    
    int ctemp = 7;
    int loop = 0;
    while (fcarry_count(&c)) {
        loop++;
        eqint(ctemp--, fcarry_count(&c));
        eqint(0, fcarry_delete(&c, 0));
        eqint(ctemp, fcarry_count(&c));
        for (i = 0; i < ctemp; i++) {
            eqint(i + loop, fcarry_getp(&c, i)->bar);
        }
        isnull(fcarry_getp(&c, i+1));
    }
    eqint(-1, fcarry_delete(&c, 0));
}


void
test_fcarry_insert() {
    struct fcarry c;
    fcarry_init(&c);

    /* Insert on empty list */
    eqint(0, fcarry_insertp(&c, 0, &f1));
    eqint(1, fcarry_getp(&c, 0)->bar);
   
    /* Insert on semi-full list */
    fcarry_appendp(&c, &f2);
    fcarry_appendp(&c, &f4);
    eqint(0, fcarry_insertp(&c, 0, &f0));
    eqint(0, fcarry_getp(&c, 0)->bar);
    eqint(1, fcarry_getp(&c, 1)->bar);
    eqint(2, fcarry_getp(&c, 2)->bar);
    eqint(4, fcarry_getp(&c, 3)->bar);

    /* Insert at the middle of the list */
    eqint(0, fcarry_insertp(&c, 3, &f3));
    eqint(0, fcarry_getp(&c, 0)->bar);
    eqint(1, fcarry_getp(&c, 1)->bar);
    eqint(2, fcarry_getp(&c, 2)->bar);
    eqint(3, fcarry_getp(&c, 3)->bar);
    eqint(4, fcarry_getp(&c, 4)->bar);

    /* Insert at the end of the list */
    eqint(0, fcarry_insertp(&c, 5, &f5));
    eqint(0, fcarry_getp(&c, 0)->bar);
    eqint(1, fcarry_getp(&c, 1)->bar);
    eqint(2, fcarry_getp(&c, 2)->bar);
    eqint(3, fcarry_getp(&c, 3)->bar);
    eqint(4, fcarry_getp(&c, 4)->bar);
    eqint(5, fcarry_getp(&c, 5)->bar);

    /* Insert at invalid position */
    eqint(-1, fcarry_insertp(&c, 7, &f8));
}
