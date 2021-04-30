COMP=gcc

ifeq ($(COMP),gcc)
CC=gcc
CCFLAGS=-g -O3 -fopenacc 
RUN=
endif

EXE=sum

all: $(EXE)

$(EXE): sum.c
	$(CC) $(CCFLAGS) $^ -o $@ 

clean:
	rm -f $(EXE) *.o *~

