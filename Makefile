
CC=clang
CFLAGS=-std=c11 -O2 -Wall -Wextra -fstack-protector -fstack-protector-all -pipe -arch x86_64 -mmacosx-version-min=10.14

therm: thermometer.c
	$(CC) $(CFLAGS) -o $@ thermometer.c

clean:
	@rm -vf therm *.o *.dSYM
