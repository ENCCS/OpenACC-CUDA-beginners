COMP=pgi

ifeq ($(COMP),pgi)
CC=pgf90
CCFLAGS=-g -O3 -acc -Minfo=accel -ta=nvidia
RUN=
else ifeq ($(COMP),gnu)
CC=gfortran
CCFLAGS=-g -O3 -fopenacc
RUN=
endif

EXE=jacobi

all: $(EXE)

$(EXE): jacobi.F90
	$(CC) $(CCFLAGS) $^ -o $@ 

clean:
	rm -f $(EXE) *.o *~

