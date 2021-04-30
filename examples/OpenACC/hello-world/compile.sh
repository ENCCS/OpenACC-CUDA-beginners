#!/bin/bash -l

gcc -g -O3 -fopenacc  -foffload=nvptx-none hello.c -o c_hello

gfortran -g -O3 -fopenacc  -foffload=nvptx-none hello.F90 -o f_hello
