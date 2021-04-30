COMP=gcc

ifeq ($(COMP),gcc)
CC=gcc
CCFLAGS=-g -O3 -fopenacc -lcurand
RUN=
endif

EXE=pi_MC_openacc

all: $(EXE)

$(EXE): pi_MC_openacc.c
	$(CC) $(CCFLAGS) $^ -o $@ 

clean:
	rm -f $(EXE) *.o *~

