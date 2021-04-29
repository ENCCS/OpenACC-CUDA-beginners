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
- file system - where to run jobs
- modules
- submitting jobs, interactive vs batch, allocation and reservation

  .. code-block::

     module use /proj/snic2021-22-274/hpc_sdk/modulefiles
     module avail nvhpc

     interactive -n 1 -c 32 --gpus-per-task=1 -t 60 -A snic2021-22-274 --reservation=openacc-cuda-workshop-2021-05-04

     

Running on Google Colab
-----------------------

