COMP=pgi

ifeq ($(COMP),pgi)
CC=pgcc
CCFLAGS=-g -O3 -acc -Minfo=accel -ta=nvidia -L/proj/snic2021-22-274/CUDA/11.2.0/lib64 -lcurand
RUN=
endif

EXE=pi_MC_openacc

all: $(EXE)

$(EXE): pi_MC_openacc.c
	$(CC) $(CCFLAGS) $^ -o $@ 

clean:
	rm -f $(EXE) *.o *~

