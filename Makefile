.PHONY: all
all: test


%.o: %.c %.h
	$(CC) -c $(CFLAGS) -o $@ $<


test_carry: test_carry.c carry_int.o
	$(CC) -o $@ $^


test: test_carry


clean:
	-rm *.o
	-rm test_carry
