# GNU compiler
CC	= icc -openmp -fp-model strict
CFLAGS	= -O2 -std=c99 -Wall -I/usr/local/include

LDLIBS	= -L/usr/local/lib -lFHBRS -lX11 -lpthread -lm


default:: nbody.exe

run:: nbody.exe
	./nbody.exe -t_end 36000000 -timesteps 100000 -bodies 1000 -nodisplay

run2:: nbody.exe
	./nbody.exe -t_end 36000000 -timesteps 10000 -bodies 1000 -nodisplay

clean::
	-rm -f *.exe *.o


nbody.exe: nbody.o
	$(CC) -o $@ $< $(LDLIBS)

nbody.o: nbody.c
	$(CC) $(CFLAGS) -c $<

