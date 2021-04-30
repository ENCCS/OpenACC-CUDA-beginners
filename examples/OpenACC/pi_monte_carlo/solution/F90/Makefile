COMP=pgi

ifeq ($(COMP),pgi)
FC=pgf90
FFLAGS=-g -O3 -acc -Minfo=accel -ta=nvidia -L/proj/snic2021-22-274/CUDA/11.2.0/lib64 -lcurand
RUN=
else ifeq ($(COMP),gnu)
CC=gfortran
CCFLAGS=-g -O3 -fopenacc -I/usr/local/cuda-11.0/include/ -L/usr/local/cuda-11.0/lib64/ -lcurand
RUN=
endif

EXE=pi_MC_openacc

all: $(EXE)

$(EXE): pi_MC_openacc.F90
	$(FC) $(FFLAGS) $^ -o $@ 

clean:
	rm -f $(EXE) *.o *~

