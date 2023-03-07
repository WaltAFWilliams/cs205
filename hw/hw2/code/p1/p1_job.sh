#!/bin/bash
#SBATCH --job-name=p1_job
#SBATCH --output=p1_job.out
#SBATCH --error=p1_job.err
#SBATCH --ntasks=1
#SBATCH --nodes=1
#SBATCH --ntasks-per-node=1
#SBATCH --cpus-per-task=32
#SBATCH --time=00:10:00
#SBATCH --mail-user=<glee@g.harvard.edu>
#SBATCH --mail-type=END

module purge 
module load gcc/12.1.0-fasrc01
module load intel/21.2.0-fasrc01
module load openmpi/4.1.3-fasrc01

make clean 
make

for p in 1 2 4 8 16 32; do
	export OMP_NUM_THREADS=$p
	echo "Number of threads: $p" >> p1_results.txt
	./julia_set >> p1_results.txt
done 





























