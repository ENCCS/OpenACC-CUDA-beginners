#!/bin/bash

module use /proj/snic2021-22-274/hpc_sdk/modulefiles
module load nvhpc

gcc vector_add.cpp -o vector_add