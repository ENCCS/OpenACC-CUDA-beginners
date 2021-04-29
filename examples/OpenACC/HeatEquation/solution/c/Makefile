COMP=pgi

ifeq ($(COMP),pgi)
CC=pgcc
CCFLAGS=-g -O3 -acc -Minfo=accel -ta=nvidia
RUN=
endif

EXE=heat
OBJS=pngwriter.o heat_equation.o 

all: $(EXE)

# Dependencies
heat_equation.o: heat_equation.c
pngwriter.o: pngwriter.c

$(EXE): $(OBJS) .ALWAYSEXEC
	$(CC) $(CCFLAGS) $(OBJS) -o $@  /usr/lib64/libpng15.so.15

%.o: %.c
	$(CC) $(CCFLAGS) -c $< -o $@

clean:
	-/bin/rm -f $(EXE)
	-/bin/rm -f a.out *.o *~ *.png

.ALWAYSEXEC:
