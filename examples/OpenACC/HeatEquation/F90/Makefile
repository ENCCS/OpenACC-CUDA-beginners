COMP=pgi

ifeq ($(COMP),pgi)
CC=pgcc
FC=pgf90
CCFLAGS=-g -O3 -acc -Minfo=accel -ta=nvidia -I /proj/snic2021-22-274/libpng/1.5.30/include
FCFLAGS=-g -O3 -acc -Minfo=accel -ta=nvidia
LFLAGS=-L/proj/snic2021-22-274/libpng/1.5.30/lib -lpng
# FCFLAGS=-g -Mbounds
RUN=
endif

EXE=heat
OBJS=pngwriter.o heat_equation.o

all: $(EXE)

# Dependencies
heat_equation.o: pngwriter.o heat_equation.F90 

$(EXE): $(OBJS) .ALWAYSEXEC
	$(FC) $(FCFLAGS) $(OBJS) $(LFLAGS) -o $@  

pngwriter.o: pngwriter.c
	$(CC) $(CCFLAGS) -c $< -o $@

%.o: %.F90
	$(FC) $(FCFLAGS) -c $< -o $@

clean:
	-/bin/rm -f $(EXE)
	-/bin/rm -f  *.o *.mod *~ *.png

.ALWAYSEXEC:
