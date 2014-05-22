CC	= cc -fopenmp
CFLAGS	= -O2 -Wall -I/usr/local/include
LDFLAGS	= -L/usr/local/lib -lFHBRS -L/usr/X11R6/lib -lX11 -lpthread -lm

default:: mandelbrot.exe

clean::
	-rm -f mandelbrot.exe mandelbrot.o

# mit grafischer Anzeige
run:: mandelbrot.exe
	./mandelbrot.exe -2 -2 2 2 50000 1
# ohne grafische Anzeige
run2:: mandelbrot.exe
	export OMP_NUM_THREADS=1
	./mandelbrot.exe -2 -2 2 2 50000 0
	export OMP_NUM_THREADS=2
	./mandelbrot.exe -2 -2 2 2 50000 0
	export OMP_NUM_THREADS=4
	./mandelbrot.exe -2 -2 2 2 50000 0
	export OMP_NUM_THREADS=8
	./mandelbrot.exe -2 -2 2 2 50000 0
	export OMP_NUM_THREADS=16
	./mandelbrot.exe -2 -2 2 2 50000 0
	export OMP_NUM_THREADS=24
	./mandelbrot.exe -2 -2 2 2 50000 0
	export OMP_NUM_THREADS=32
	./mandelbrot.exe -2 -2 2 2 50000 0
	export OMP_NUM_THREADS=48
	./mandelbrot.exe -2 -2 2 2 50000 0
	export OMP_NUM_THREADS=64
	./mandelbrot.exe -2 -2 2 2 50000 0
mandelbrot.exe: mandelbrot.o
	$(CC) -o $@ $< $(LDFLAGS)

mandelbrot.o: mandelbrot.c
	$(CC) $(CFLAGS) -c $<

