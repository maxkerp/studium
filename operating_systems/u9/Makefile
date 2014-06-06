CFLAGS=-Wall -g
LDFLAGS=-lpthread
CC=cc

all:
	$(CC) $(CFLAGS) %.c -o $<

$<: %.c
	$(CC) $(CFLAGS) -lpthread

clean:
	rm -f *ex
