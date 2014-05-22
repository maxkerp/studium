# GNU compiler
CC	= cc -fopenmp
# Intel OpenMP compiler
#CC	= icc -openmp

CFLAGS	= -O0 -g -Wall -std=c99 -I/usr/local/include
LDLIBS	= -L/usr/local/lib -lFHBRS -L/usr/X11R6/lib -ltiff -lX11 -lpthread -lm


default:: image.exe

# mit grafischer Ausgabe
run:: image.exe
	./image.exe Test.tiff

# ohne grafische Ausgabe
run2:: image.exe
	export OMP_NUM_THREADS=1
	./image.exe -n Test.tiff
	export OMP_NUM_THREADS=2
	./image.exe -n Test.tiff
	export OMP_NUM_THREADS=4
	./image.exe -n Test.tiff
	export OMP_NUM_THREADS=8
	./image.exe -n Test.tiff
	export OMP_NUM_THREADS=12
	./image.exe -n Test.tiff
	export OMP_NUM_THREADS=16
	./image.exe -n Test.tiff
	export OMP_NUM_THREADS=24
	./image.exe -n Test.tiff
	export OMP_NUM_THREADS=32
	./image.exe -n Test.tiff
	export OMP_NUM_THREADS=48
	./image.exe -n Test.tiff
	export OMP_NUM_THREADS=64
	./image.exe -n Test.tiff

clean::
	-rm -f *.exe *.o

image.exe: main.o tiff.o rgb.o gray.o edgedetect.o
	$(CC) -o $@ $^ $(LDLIBS)

edgedetect.o: edgedetect.c edgedetect.h commondefs.h gray.h rgb.h
gray.o: gray.c commondefs.h rgb.h gray.h
main.o: main.c tiff.h rgb.h gray.h commondefs.h edgedetect.h
rgb.o: rgb.c commondefs.h rgb.h gray.h
tiff.o: tiff.c tiff.h rgb.h gray.h commondefs.h
