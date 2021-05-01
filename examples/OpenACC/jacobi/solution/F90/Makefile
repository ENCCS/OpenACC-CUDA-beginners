COMP=pgi

ifeq ($(COMP),pgi)
FC=pgf90
FFLAGS=-g -O3 -acc -Minfo=accel -ta=nvidia
RUN=
endif

EXE=jacobi

all: $(EXE)

$(EXE): jacobi.F90
	$(FC) $(FFLAGS) $^ -o $@ 

clean:
	rm -f $(EXE) *.o *~

