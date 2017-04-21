FLAGS=-D_LINUX -ffast-math -funroll-loops -O3 -g
FLAGS_NO=-D_LINUX -g
LIBS=-lGL -lglut -lGLU
INCDIR=-I../include
LIBDIR=-L../lib -L/usr/X11R6/lib
OBJDIR=build/obj/
CC=gcc

SRC=src/ray_tracer.c src/ops.c src/tracer.c
BLD=build/ray_tracer

make:
	mkdir build
	$(CC) $(SRC) $(FLAGS) $(INCDIR) $(LIBDIR) $(LIBS) -o $(BLD)

no_opt:
	mkdir build
	$(CC) $(SRC) $(FLAGS_NO) $(INCDIR) $(LIBDIR) $(LIBS) -o $(BLD)

clean:
	rm -rf build

run:
	$(BLD)
