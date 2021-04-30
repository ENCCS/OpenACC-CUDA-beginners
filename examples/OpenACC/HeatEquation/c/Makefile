COMP=gcc

ifeq ($(COMP),gcc)
CC=gcc
CCFLAGS=-g -O3 -fopenacc
LFLAGS=
RUN=
endif

EXE=heat
OBJS=heat_equation.o 

all: $(EXE)

# Dependencies
heat_equation.o: heat_equation.c

$(EXE): $(OBJS) .ALWAYSEXEC
	$(CC) $(CCFLAGS) $(OBJS) $(LFLAGS) -o $@

%.o: %.c
	$(CC) $(CCFLAGS) -c $< -o $@

clean:
	-/bin/rm -f $(EXE)
	-/bin/rm -f a.out *.o *~ *.png

.ALWAYSEXEC:
