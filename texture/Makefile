FLAGS=-D_LINUX -ffast-math -funroll-loops -O3 -g
FLAGS_NO=-D_LINUX -g
LIBS=-lGL -lglut -lGLU -lSOIL
INCDIR=-I../include
LIBDIR=-L../lib -L/usr/X11R6/lib
OBJDIR=build/obj/
CC=gcc

make:
	$(CC) texture.c $(FLAGS) $(INCDIR) $(LIBDIR) $(LIBS) -o texture

no_opt:
	$(CC) texture.c $(FLAGS_NO) $(INCDIR) $(LIBDIR) $(LIBS) -o texture

clean:
	rm texture
	rm -rf vgcore.*
