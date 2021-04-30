COMP=pgi

ifeq ($(COMP),pgi)
CC=pgcc
CCFLAGS=-g -O3 -acc -Minfo=accel -ta=nvidia
RUN=
else ifeq ($(COMP),gnu)
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

