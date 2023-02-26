#!/usr/bin/env bash
#SBATCH --job-name=hybrid_4nodes
#SBATCH --output=hybrid_4nodes_%j.out
#SBATCH --error=hybrid_4nodes_%j.err
#SBATCH --nodes=4
#SBATCH --ntasks-per-node=1
#SBATCH --cpus-per-task=32
#SBATCH --time=00:30:00
# set the number of OpenMP threads per MPI process
# (more on this in class later)
export OMP_NUM_THREADS=$SLURM_CPUS_PER_TASK
# here we run our program: see man srun
#
# * srun is the SLURM runner similar to mpirun (more on this in class)
# * we also add "$@" here to forward any arguments to our program that
#   were passed to the job script at submission time.
# * note that the submission script assumes that the hybrid_node program
#   is in the same directory (./)
srun ./hybrid_node "$@"
# return the exit code of srun above
exit $?
