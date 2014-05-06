CC	= cc
CFLAGS	= -O2 -g -Wall -std=c99
LDFLAGS	= -lpthread -lm

default:: a1.exe

a2: a2.exe

clean::
	-rm -f *.exe *.o

run:: a1.exe
	./$< | less

a1.exe: a1.o
	$(CC) -o $@ $< $(LDFLAGS)

a1.o: a1.c
	$(CC) $(CFLAGS) -c $<

a2.exe: a2.o
	$(CC) -o $@ $< $(LDFLAGS)

a2.o: a2.c
	$(CC) $(CFLAGS) -c $<
