FLAGS=-D_LINUX -ffast-math -funroll-loops -O0 -g -std=gnu99 -trigraphs
LIBS=-lGL -lglut -lGLU -lm
INCDIR=-I../include
LIBDIR=-L../lib -L/usr/X11R6/lib
CC=gcc

asgn5: ray_tracer.c
	$(CC) ray_tracer.c $(FLAGS) $(INCDIR) $(LIBDIR) $(LIBS) -o tracer
clean:
	rm tracer
run:
	./tracer
