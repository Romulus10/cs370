FLAGS=-D_LINUX -ffast-math -funroll-loops -O3 -g
LIBS=-lGL -lglut -lGLU
INCDIR=-I../include
LIBDIR=-L../lib -L/usr/X11R6/lib
OBJDIR=build/obj/
CC=gcc

make:
	mkdir build
	$(CC) src/project2.c lib/matrix.c $(FLAGS) $(INCDIR) $(LIBDIR) $(LIBS) -o build/project2

clean:
	rm -rf build
	rm -rf vgcore.*
