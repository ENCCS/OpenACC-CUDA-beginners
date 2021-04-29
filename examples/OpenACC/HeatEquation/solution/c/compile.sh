#!/bin/bash -l

module use /proj/snic2021-22-274/hpc_sdk/modulefiles
module add nvhpc
#
make clean
make
