#!/bin/make
CC=/pkg/main/sys-devel.gcc.core/bin/x86_64-pc-linux-gnu-gcc
CFLAGS=-Wall -g -ggdb -O2 -pipe -U_FORTIFY_SOURCE -D_FORTIFY_SOURCE=2 -D__STDC_FORMAT_MACROS -fPIC -pthread -ftrivial-auto-var-init=zero

TARGET=monadebug
OBJECTS=bmw.o main.o

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	$(RM) $(OBJECTS)
