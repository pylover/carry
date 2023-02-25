.PHONY: all
all: test


caryy_int: carry.c carry_int.h
	$(CC) -c $(CFLAGS) -DT=int -o $@ $<


%.o: %.c %.h
	$(CC) -c $(CFLAGS) -o $@ $<


test_carry: test_carry.c carry_int.o
	$(CC) -o $@ $^


test: test_carry

