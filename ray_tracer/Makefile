FLAGS=-D_LINUX -ffast-math -funroll-loops -O3 -g
FLAGS_NO=-D_LINUX -g
LIBS=-lGL -lglut -lGLU
INCDIR=-I../include
LIBDIR=-L../lib -L/usr/X11R6/lib
OBJDIR=build/obj/
CC=gcc

make:
	mkdir build
	$(CC) src/ray_tracer.c src/ops.c $(FLAGS) $(INCDIR) $(LIBDIR) $(LIBS) -o build/ray_tracer

no_opt:
	mkdir build
	$(CC) src/ray_tracer.c src/ops.c $(FLAGS_NO) $(INCDIR) $(LIBDIR) $(LIBS) -o build/ray_tracer

clean:
	rm -rf build

run:
	build/ray_tracer
