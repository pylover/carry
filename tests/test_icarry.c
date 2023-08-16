static int i0 = 0;
static int i1 = 1;
static int i2 = 2;
static int i3 = 3;
static int i4 = 4;
static int i5 = 5;
static int i6 = 6;
static int i7 = 7;
static int i8 = 8;
static int i9 = 9;


void
test_iinit() {
    int i;
    int tmp;
    struct ints c;

    eqint(0, iinit(&c));
    eqint(0, icount(&c));
    eqint(true, iisempty(&c));
    eqint(false, iisfull(&c));
    for (i = 0; i < CSIZE; i++) {
        eqint(-1, icopy(&c, &tmp, i));
    }
}


void
test_iappend() {
    int i;
    struct ints c;
    iinit(&c);
    
    for (i = 0; i < CSIZE; i++) {
        eqint(0, iappendp(&c, &i));
    }
    eqint(8, icount(&c));
    eqint(-1, iappendp(&c, &i8));
    eqint(8, icount(&c));
}


void
test_idelete() {
    int i;
    struct ints c;
    iinit(&c);
    
    for (i = 0; i < CSIZE; i++) {
        iappendp(&c, &i);
    }
    eqint(8, icount(&c));
    eqint(0, *igetp(&c, 0));
  
    eqint(0, idelete(&c, 7));
    eqint(7, icount(&c));
    for (i = 0; i < 7; i++) {
        eqint(i, *igetp(&c, i));
    }
    
    int ctemp = 7;
    int loop = 0;
    while (icount(&c)) {
        loop++;
        eqint(ctemp--, icount(&c));
        eqint(0, idelete(&c, 0));
        eqint(ctemp, icount(&c));
        for (i = 0; i < ctemp; i++) {
            eqint(i + loop, *igetp(&c, i));
        }
        isnull(igetp(&c, i+1));
    }
    eqint(-1, idelete(&c, 0));
}


void
test_iinsert() {
    struct ints c;
    iinit(&c);

    /* Insert on empty list */
    eqint(0, iinsertp(&c, 0, &i1));
    eqint(1, *igetp(&c, 0));
   
    /* Insert on semi-full list */
    iappendp(&c, &i2);
    iappendp(&c, &i4);
    eqint(0, iinsertp(&c, 0, &i0));
    eqint(0, *igetp(&c, 0));
    eqint(1, *igetp(&c, 1));
    eqint(2, *igetp(&c, 2));
    eqint(4, *igetp(&c, 3));

    /* Insert at the middle of the list */
    eqint(0, iinsertp(&c, 3, &i3));
    eqint(0, *igetp(&c, 0));
    eqint(1, *igetp(&c, 1));
    eqint(2, *igetp(&c, 2));
    eqint(3, *igetp(&c, 3));
    eqint(4, *igetp(&c, 4));

    /* Insert at the end of the list */
    eqint(0, iinsertp(&c, 5, &i5));
    eqint(0, *igetp(&c, 0));
    eqint(1, *igetp(&c, 1));
    eqint(2, *igetp(&c, 2));
    eqint(3, *igetp(&c, 3));
    eqint(4, *igetp(&c, 4));
    eqint(5, *igetp(&c, 5));

    /* Insert at invalid position */
    eqint(-1, iinsertp(&c, 7, &i8));
}
