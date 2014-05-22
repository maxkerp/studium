#!/bin/sh
#PBS -q wr17
#PBS -l nodes=1:ppn=48
#PBS -l walltime=01:00:00
#PBS -l vmem=16GB

# change to job submit directory
cd $PBS_O_WORKDIR

echo "Programm wird ausgeführt auf " `hostname`
# Achtung: dies ist noetig wegen eines groesseren Stacks!!
ulimit -s 10000000

# ausführen ohne Grafikausgabe
make run2

exit
