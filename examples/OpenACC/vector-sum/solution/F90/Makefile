COMP=gcc

ifeq ($(COMP),gcc)
CC=gfortran
CCFLAGS=-g -O3 -fopenacc
RUN=
endif

EXE=sum

all: $(EXE)

$(EXE): sum.F90
	$(CC) $(CCFLAGS) $^ -o $@ 

clean:
	rm -f $(EXE) *.o *~

