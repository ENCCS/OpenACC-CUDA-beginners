COMP=pgi

ifeq ($(COMP),pgi)
CC=pgcc
CCFLAGS=-g -O3 -acc -Minfo=accel -ta=nvidia -lcurand
RUN=
endif

EXE=pi_MC_openacc

all: $(EXE)

$(EXE): pi_MC_openacc.c
	$(CC) $(CCFLAGS) $^ -o $@ 

clean:
	rm -f $(EXE) *.o *~

