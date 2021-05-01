COMP=pgi

ifeq ($(COMP),pgi)
FC=pgf90
FFLAGS=-g -O3 -acc -Minfo=accel -ta=nvidia
RUN=
endif

EXE=sum

all: $(EXE)

$(EXE): sum.F90
	$(FC) $(FFLAGS) $^ -o $@ 

clean:
	rm -f $(EXE) *.o *~

