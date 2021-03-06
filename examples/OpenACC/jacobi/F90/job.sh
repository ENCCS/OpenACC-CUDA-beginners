#!/bin/bash
#SBATCH --account=snic2021-22-274
#SBATCH --ntasks=1
#SBATCH --gpus-per-task=1
#SBATCH --time=00:15:00
#SBATCH --reservation=openacc-cuda-workshop-2021-05-04

module use /proj/snic2021-22-274/hpc_sdk/modulefiles
module load nvhpc

srun ./jacobi

# Submit to the batch job queue with the command:
#  sbatch job.sh

# or alternatively, run directly from the command line:
#  srun --account=snic2021-22-274 --ntasks=1 --time=00:15:00 --gpus-per-task=1 \
#       ./jacobi
