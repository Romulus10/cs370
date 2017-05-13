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
cleanup:
	clang-format ray_tracer.c > tmp.txt
	cat tmp.txt > ray_tracer.c
	rm tmp.txt
all:
	make cleanup
	make clean
	make asgn5
	make run
