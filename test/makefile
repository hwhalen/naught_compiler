NCC = ../comp
CPP = cpp
CC = gcc
INCDIRS = -I ../nstdlib
CFLAGS = -c -g -Wall -std=c99
LDFLAGS = -L ../nstdlib -lnaught

EXES = example test_int test_basic test_string test_string_add

.PRECIOUS: %.c

all: $(EXES)

example: example.o fact.o initLabel.o ../comp
	 $(CC) example.o fact.o initLabel.o -o example $(LDFLAGS)
	 ./example

test_int: test_int.o ../comp
	 $(CC) test_int.o -o test_int $(LDFLAGS)
	 ./test_int

test_basic: test_basic.o ../comp
	$(CC)  test_basic.o -o test_basic $(LDFLAGS)
	./test_basic

test_string:  test_string.o ../comp
			 $(CC) test_string.o -o test_string $(LDFLAGS)
			 ./test_string

test_string_add:  test_string_add.o ../comp
			 $(CC) test_string_add.o -o test_string_add $(LDFLAGS)
			 ./test_string_add

%.c : %.n ../comp
		$(CPP) $(INCDIRS) $< | $(NCC) -d -o $@ -
		cat $@

%.o : %.c
		$(CC) $(CFLAGS) $(INCDIRS) $<

clean:
	rm -f *~ *.o *.c $(EXES)
