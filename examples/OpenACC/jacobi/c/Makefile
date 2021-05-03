COMP=gcc

ifeq ($(COMP),gcc)
CC=gcc
CCFLAGS=-g -O3 -fopenacc 
RUN=
endif

EXE=jacobi

all: $(EXE)

$(EXE): jacobi.c
	$(CC) $(CCFLAGS) $^ -o $@ 

clean:
	rm -f $(EXE) *.o *~

