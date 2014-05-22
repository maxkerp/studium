#!/bin/sh
#PBS -q wr17
#PBS -l nodes=1:ppn=48
#PBS -l walltime=01:00:00

# change to job submit directory
cd $PBS_O_WORKDIR

echo "Programm wird ausgeführt auf " `hostname`

# ausführen ohne Grafikausgabe
make run2

exit
