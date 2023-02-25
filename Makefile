.PHONY: all
all: test


%.o: %.c %.h
	$(CC) -c $(CFLAGS) -o $@ $<


test_carry_int: test_carry_int.c carry_int.o
	$(CC) -o $@ $^


test_carry_char: test_carry_char.c carry_char.o
	$(CC) -o $@ $^


test: test_carry_int test_carry_char
	./test_carry_int
	./test_carry_char


clean:
	-rm *.o
	-rm test_carry_int
	-rm test_carry_char
