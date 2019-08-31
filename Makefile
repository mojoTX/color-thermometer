
CC=clang
CFLAGS=-std=c11 -O2 -Wall -Wextra -fstack-protector -fstack-protector-all -pipe

OS=$(shell uname -s )

ifeq ($(OS), Darwin)
CFLAGS+=-arch x86_64 -mmacosx-version-min=10.14
endif

therm: thermometer.c
	$(CC) $(CFLAGS) -o $@ thermometer.c

clean:
	@rm -vf therm *.o *.dSYM
