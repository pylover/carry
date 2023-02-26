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
test_finit() {
    int i;
    struct foo tmp;
    struct foos c;

    eqint(0, finit(&c));
    eqint(0, fcount(&c));
    eqint(true, fisempty(&c));
    eqint(false, fisfull(&c));
    for (i = 0; i < CSIZE; i++) {
        eqint(-1, fcopy(&c, &tmp, i));
    }
}


void
test_fappend() {
    char i;
    struct foos c;
    finit(&c);
    
    for (i = 0; i < CSIZE; i++) {
        eqint(0, fappendp(&c, foos[i]));
    }
    eqint(8, fcount(&c));
    eqint(-1, fappendp(&c, &f8));
    eqint(8, fcount(&c));
}


void
test_fdelete() {
    char i;
    struct foos c;
    finit(&c);
    
    for (i = 0; i < CSIZE; i++) {
        fappendp(&c, foos[i]);
    }
    eqint(8, fcount(&c));
    eqint(0, fgetp(&c, 0)->bar);
  
    eqint(0, fdelete(&c, 7));
    eqint(7, fcount(&c));
    for (i = 0; i < 7; i++) {
        eqint(i, fgetp(&c, i)->bar);
    }
    
    int ctemp = 7;
    int loop = 0;
    while (fcount(&c)) {
        loop++;
        eqint(ctemp--, fcount(&c));
        eqint(0, fdelete(&c, 0));
        eqint(ctemp, fcount(&c));
        for (i = 0; i < ctemp; i++) {
            eqint(i + loop, fgetp(&c, i)->bar);
        }
        isnull(fgetp(&c, i+1));
    }
    eqint(-1, fdelete(&c, 0));
}


void
test_finsert() {
    struct foos c;
    finit(&c);

    /* Insert on empty list */
    eqint(0, finsertp(&c, 0, &f1));
    eqint(1, fgetp(&c, 0)->bar);
   
    /* Insert on semi-full list */
    fappendp(&c, &f2);
    fappendp(&c, &f4);
    eqint(0, finsertp(&c, 0, &f0));
    eqint(0, fgetp(&c, 0)->bar);
    eqint(1, fgetp(&c, 1)->bar);
    eqint(2, fgetp(&c, 2)->bar);
    eqint(4, fgetp(&c, 3)->bar);

    /* Insert at the middle of the list */
    eqint(0, finsertp(&c, 3, &f3));
    eqint(0, fgetp(&c, 0)->bar);
    eqint(1, fgetp(&c, 1)->bar);
    eqint(2, fgetp(&c, 2)->bar);
    eqint(3, fgetp(&c, 3)->bar);
    eqint(4, fgetp(&c, 4)->bar);

    /* Insert at the end of the list */
    eqint(0, finsertp(&c, 5, &f5));
    eqint(0, fgetp(&c, 0)->bar);
    eqint(1, fgetp(&c, 1)->bar);
    eqint(2, fgetp(&c, 2)->bar);
    eqint(3, fgetp(&c, 3)->bar);
    eqint(4, fgetp(&c, 4)->bar);
    eqint(5, fgetp(&c, 5)->bar);

    /* Insert at invalid position */
    eqint(-1, finsertp(&c, 7, &f8));
}
