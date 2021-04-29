.. _setup

Setup
=====

In order to follow type-along sessions and do exercises in this lesson
you will need access to a computational resource with GPUs and
installations of CUDA and compilers supporting OpenACC.

.. callout:: Where to run the exercises

   During an ENCCS workshop the primary way to do the exercises is to use
   the cluster available to workshop participants. You can find instruction
   for the Tetralith cluster below.

   If you do not have access to Tetralith but you have a user account on another
   GPU cluster you can use that instead - note however that you will need to
   adapt the instructions below according to the specifics of that cluster.

   If you do not have access to any GPU cluster, you can follow the instructions
   below on how to use Google Colab.
   

Running on Tetralith
--------------------

- how to log in

On any Linux systems and Mac OS system, using command ::

  ssh  <username>@tetralith.nsc.liu.se

to login on the Tetralith (**tetralith.nsc.liu.se**) at NSC supercomputing center.

On Windows system, you need to install **putty** and then login on the Tetralith, more details can be found at https://www.nsc.liu.se/support/systems/tetralith-getting-started

- file system - where to run jobs

When you login on the Tetralith system, you can read the welcome messages (motd) ::

 Welcome to NSC and Tetralith!

 **** Project storage directories available to you:
 /proj/snic2021-22-274/users/x_username

 **** Documentation and getting help:
 https://www.nsc.liu.se/support/systems/tetralith-getting-started/
 https://www.nsc.liu.se/support

 **** Useful commands
 To see your active projects and CPU time usage: projinfo
 To see available disk storage and usage: snicquota
 To see your last jobs: lastjobs
 Login to compute node to check running job: jobsh

 To tweak job priorities, extend timelimits and reserve nodes: see
 https://www.nsc.liu.se/support/batch-jobs/boost-tools/

In this workshop, we will recommend to use project folder i.e.  **/proj/snic2021-22-274/users/<your_username>** to do these exercises :: 

 $ cd /proj/snic2021-22-274/users/<your_username>
 $ git clone https://github.com/ENCCS/OpenACC-CUDA-beginners.git
 $ cd OpenACC-CUDA-beginners

- modules
Likes other HPC center, modules system is used tomaintain and use large set of programs at NSC. The main usages of modules system are presented below ::
 module --help         General help with module commands

 module avail          List the available modules and recommendations

 module load ...       Load the selected modules into your session (can also write: module add)

 module list           List your currently loaded modules (will be flushed at logout)

 module rm ...         Remove selected modules from your session

 module purge          Remove all loaded modules

 module use ...        Use the modulefile which is not installed in default path

More information about module system at NSC can be found at https://www.nsc.liu.se/software/modules

- submitting jobs, interactive vs batch, allocation and reservation

NSC uses the Slurm workload Manage as the workload management and job scheduling. You can either run program interactively

  .. code-block::
         
     # book a GPU compute node for 1 hour
     # using project ID "snic2021-22-274" for the workshop
     # and reservation "openacc-cuda-workshop-2021-05-04" for first day
     $ interactive -n 1 -c 32 --gpus-per-task=1 -t 60 -A snic2021-22-274 --reservation=openacc-cuda-workshop-2021-05-04
     ...
     
or in batch mode with a job script ::
     $ sbatch job.sh

- Summary 

Here is a sample process to run OpenACC program on Tetralith ::

  # login on Tetralib from local computer
  local_computer $ ssh <your_username>@tetralith.nsc.liu.se
  ...
  # use /proj/snic2021-22-274 folder
  tetralith $ cd /proj/snic2021-22-274/users/<your_username>

  # git the course material
  tetralith $ git clone https://github.com/ENCCS/OpenACC-CUDA-beginners.git

  # Use the example c code for vector addition
  tetralith $ cd OpenACC-CUDA-beginners/examples/OpenACC/vector-sum/c

  # Load the nvhpc module for using pgcc/pgf90 compiler
  tetralith $ module use /proj/snic2021-22-274/hpc_sdk/modulefiles
  tetralith $ module avail nvhpc

  # compile the code (or direct use "make")
  tetralith $ ./compile.sh

  # check if the binary created
  tetralith $ ls
   Makefile  compile.sh  job.sh  sum  sum.c

  # run the binary "sum" on GPU, 
  tetralith $ sbatch job.sh
   
  # or directly use "srun ... ./sum"
  tetralith $ srun -n 1  --gpus-per-task=1 -t 10 -A snic2021-22-274 --reservation=openacc-cuda-workshop-2021-05-04 ./sum

  # or run interactive
  tetralith $ interactive -n 1 -c 32 --gpus-per-task=1 -t 60 -A snic2021-22-274 --reservation=openacc-cuda-workshop-2021-05-04
  salloc: job 13170656 has been allocated resources
  salloc: Granted job allocation 13170656
  srun: Step created for job 13170656
  
  # Note: compute node has been assigned, check using command "hostname"
  # should direct run the binary
  n1141 $ ./sum
   Reduction sum: 1.2020569031119108
     

Running on Google Colab
-----------------------

