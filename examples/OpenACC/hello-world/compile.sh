#!/bin/bash -l

module use /proj/snic2021-22-274/hpc_sdk/modulefiles
module add nvhpc
#
pgcc  -g -O3 -acc -Minfo=accel ./hello.c -o c_hello
pgf90 -g -O3 -acc -Minfo=accel ./hello.F90 -o f_hello

