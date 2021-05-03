COMP=gcc

ifeq ($(COMP),gcc)
CC=gcc
CCFLAGS=-g -O3 -fopenacc 
RUN=
endif

EXE=doubleloop

all: $(EXE)

$(EXE): doubleloop.c
	$(CC) $(CCFLAGS) $^ -o $@ 

clean:
	rm -f $(EXE) *.o *~

