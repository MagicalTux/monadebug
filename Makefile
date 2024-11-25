#!/bin/make
#CC=/pkg/main/sys-devel.gcc.core/bin/x86_64-pc-linux-gnu-gcc
CFLAGS=-Wall -g -ggdb -O2 -pipe -Wall -Wextra -Wuninitialized -Wmaybe-uninitialized -Wshadow -Wstrict-aliasing=2

TARGET=monadebug
OBJECTS=bmw.o main.o

.PHONY: clean test

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	$(RM) $(OBJECTS)

test: $(TARGET)
	./monadebug
