#!/bin/sh
#PBS -q wr8
#PBS -l nodes=1:ppn=48
#PBS -l walltime=01:00:00
#PBS -l vmem=16GB

# change to job submit directory
cd $PBS_O_WORKDIR

module load intel-icc

echo "Programm wird ausgeführt auf " `hostname`
# Achtung: dies ist noetig wegen eines groesseren Stacks!!
ulimit -s 128000

# ausführen ohne Grafikausgabe
for threads in 1 2 4 8 16 24 32 48; do
	echo "**********************" $threads "**************************"
	export OMP_NUM_THREADS=$threads
	make run2
done

exit
