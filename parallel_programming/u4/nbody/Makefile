# GNU compiler
CC	= cc -fopenmp
CFLAGS	= -O2 -std=c99 -Wall -I/usr/local/include

# Intel OpenMP compiler
#CC	= icc
#CFLAGS	= -O2 -std=c99 -I/usr/local/include

LDLIBS	= -L/usr/local/lib -lFHBRS -L/usr/X11R6/lib -lX11 -lpthread -lm


default:: nbody.exe

run:: nbody.exe
	./nbody.exe -t_end 36000000 -timesteps 10000 -bodies 1000

run2:: nbody.exe
	export OMP_NUM_THREADS=1
	./nbody.exe -t_end 36000000 -timesteps 10000 -bodies 1000 -nodisplay
	export OMP_NUM_THREADS=2
	./nbody.exe -t_end 36000000 -timesteps 10000 -bodies 1000 -nodisplay
	export OMP_NUM_THREADS=4
	./nbody.exe -t_end 36000000 -timesteps 10000 -bodies 1000 -nodisplay
	export OMP_NUM_THREADS=8
	./nbody.exe -t_end 36000000 -timesteps 10000 -bodies 1000 -nodisplay
	export OMP_NUM_THREADS=12
	./nbody.exe -t_end 36000000 -timesteps 10000 -bodies 1000 -nodisplay
	export OMP_NUM_THREADS=16
	./nbody.exe -t_end 36000000 -timesteps 10000 -bodies 1000 -nodisplay
	export OMP_NUM_THREADS=24
	./nbody.exe -t_end 36000000 -timesteps 10000 -bodies 1000 -nodisplay
	export OMP_NUM_THREADS=32
	./nbody.exe -t_end 36000000 -timesteps 10000 -bodies 1000 -nodisplay
	export OMP_NUM_THREADS=48
	./nbody.exe -t_end 36000000 -timesteps 10000 -bodies 1000 -nodisplay
	export OMP_NUM_THREADS=64
	./nbody.exe -t_end 36000000 -timesteps 10000 -bodies 1000 -nodisplay

clean::
	-rm -f *.exe *.o


nbody.exe: nbody.o
	$(CC) -o $@ $< $(LDLIBS)

nbody.o: nbody.c
	$(CC) $(CFLAGS) -c $<

