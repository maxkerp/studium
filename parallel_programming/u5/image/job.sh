#!/bin/sh
#PBS -q wr6
#PBS -l nodes=1:ppn=12
#PBS -l walltime=00:10:00
#PBS -l vmem=8GB

# change to job submit directory
cd $PBS_O_WORKDIR

module load intel-icc

echo "Programm wird ausgeführt auf " `hostname`
# Achtung: dies ist noetig wegen eines groesseren Stacks!!
ulimit -s 128000

# ausführen ohne Grafikausgabe
for nthreads in 1 16 32 64 128 160 240; do
	echo "*****************************" $nthreads "****************************"
	export OMP_NUM_THREADS=$nthreads
	make run2
done

exit
