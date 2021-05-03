COMP=pgi

ifeq ($(COMP),pgi)
CC=pgcc
CCFLAGS=-g -O3 -acc -Minfo=accel -ta=nvidia
RUN=
endif

EXE=jacobi

all: $(EXE)

$(EXE): jacobi.c
	$(CC) $(CCFLAGS) $^ -o $@ 

clean:
	rm -f $(EXE) *.o *~

