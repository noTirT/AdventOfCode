CC = gcc
CFLAGS = -Wall -O2 -Ilib

LIBSRC = $(wildcard lib/*.c)

LIBOBJ = $(LIBSRC:.c=.o)

DAYMAINS = $(wildcard day*/main.c)

EXES = $(DAYMAINS:.c=)

.PHONY: all clean

all: $(EXES)

%/main: %/main.c $(LIBOBJ)
	$(CC) $(CFLAGS) $^ -o $@

lib/%.o: lib/%.c lib/%.h
	$(CC) $(CLAGS) -c $< -o $@

clean:
	rm -rf $(EXES) $(LIBOBJ)
