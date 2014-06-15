CFLAGS=-Wall -g -std=gnu99
CC=gcc

all:
	$(CC) $(CFLAGS) %.c -o $<

$<: %.c
	$(CC) $(CFLAGS)

clean:
	rm -f *ex
