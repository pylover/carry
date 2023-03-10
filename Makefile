.PHONY: all
all: test


%.o: %.c %.h
	$(CC) -c $(CFLAGS) -o $@ $<


test_carry: test_carry.c icarry.o fcarry.o
	$(CC) -o $@ $^


test: test_carry
	./test_carry


clean:
	-rm *.o
	-rm test_carry
