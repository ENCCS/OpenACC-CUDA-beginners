COMP=pgi

ifeq ($(COMP),pgi)
CC=pgcc
CCFLAGS=-g -O3 -acc -Minfo=accel -ta=nvidia -I/proj/snic2021-22-274/libpng/1.5.30/include
LFLAGS=-L/proj/snic2021-22-274/libpng/1.5.30/lib -lpng
RUN=
endif

EXE=heat
OBJS=pngwriter.o heat_equation.o 

all: $(EXE)

# Dependencies
heat_equation.o: heat_equation_openacc_1.c
pngwriter.o: pngwriter.c

$(EXE): $(OBJS) .ALWAYSEXEC
	$(CC) $(CCFLAGS) $(OBJS) $(LFLAGS) -o $@

%.o: %.c
	$(CC) $(CCFLAGS) -c $< -o $@

clean:
	-/bin/rm -f $(EXE)
	-/bin/rm -f a.out *.o *~ *.png

.ALWAYSEXEC:
