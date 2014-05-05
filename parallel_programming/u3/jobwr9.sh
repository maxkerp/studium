#!/bin/sh
#PBS -q wr9
#PBS -l nodes=1:ppn=64
#PBS -l walltime=03:00:00
#PBS -l vmem=120GB

# change to job submit directory
cd $PBS_O_WORKDIR

module load java
height=28

for nthreads in 1 2 4 8 16 32 48 64; do
    for level in 2 4 6 8 10 12 14 16 18; do
#	echo "binary tree of height " $height ", parallel level at " $level " using " $nthreads " threads"
	java -Xms80G -Xmx80g TreeCalculation $height $level $nthreads
    done
done

exit
