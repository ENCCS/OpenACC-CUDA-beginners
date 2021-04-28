COMP=pgi

ifeq ($(COMP),pgi)
CC=pgcc
FC=pgf90
CCFLAGS=-g -O3 -acc -Minfo=accel -ta=nvidia
FCFLAGS=-g -O3 -acc -Minfo=accel -ta=nvidia
# FCFLAGS=-g -Mbounds
RUN=
endif

EXE=heat
OBJS=pngwriter.o heat_equation.o

all: $(EXE)

# Dependencies
heat_equation.o: pngwriter.o heat_equation.F90 

$(EXE): $(OBJS) .ALWAYSEXEC
	$(FC) $(FCFLAGS) $(OBJS) -o $@  /usr/lib64/libpng15.so.15

pngwriter.o: pngwriter.c
	$(CC) $(CCFLAGS) -c $< -o $@

%.o: %.F90
	$(FC) $(FCFLAGS) -c $< -o $@

clean:
	-/bin/rm -f $(EXE)
	-/bin/rm -f  *.o *.mod *~ *.png

.ALWAYSEXEC:
