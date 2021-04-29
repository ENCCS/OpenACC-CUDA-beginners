COMP=pgi

ifeq ($(COMP),pgi)
FC=pgf90
FFLAGS=-g -O3 -acc -Minfo=accel -ta=nvidia -lcurand
RUN=
endif

EXE=pi_MC_openacc

all: $(EXE)

$(EXE): pi_MC_openacc.F90
	$(FC) $(FFLAGS) $^ -o $@ 

clean:
	rm -f $(EXE) *.o *~

