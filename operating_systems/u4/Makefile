CC	= cc
CFLAGS	= -O2 -g -Wall -std=c99
LDFLAGS	= -lpthread -lm

default:: a1.exe

clean::
	-rm -f *.exe *.o

# kleines Testbeispiel
run:: a1.exe
	./$< 4 2

a1.exe: a1.o
	$(CC) -o $@ $< $(LDFLAGS)

a1.o: a1.c
	$(CC) $(CFLAGS) -c $<
