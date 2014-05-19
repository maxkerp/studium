CFLAGS=-Wall -g -std=c99
CC=cc

all:
	$(CC) $(CFLAGS) %.c -o $<

$<: %.c
	$(CC) $(CFLAGS)

clean:
	rm -f *ex
