COMP=pgi

ifeq ($(COMP),pgi)
CC=pgf90
CCFLAGS=-g -O3 -acc -Minfo=accel -ta=nvidia
RUN=
endif

EXE=doubleloop

all: $(EXE)

$(EXE): doubleloop.F90
	$(CC) $(CCFLAGS) $^ -o $@ 

clean:
	rm -f $(EXE) *.o *~

