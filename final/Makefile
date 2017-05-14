FLAGS=-D_LINUX -ffast-math -funroll-loops -O0 -g -std=gnu99 -trigraphs -Werror -Wall
LIBS=-lGL -lglut -lGLU -lm
INCDIR=-I../include
LIBDIR=-L../lib -L/usr/X11R6/lib
CC=gcc
BLD=./tracer

make: ray_tracer.c
	$(CC) ray_tracer.c $(FLAGS) $(INCDIR) $(LIBDIR) $(LIBS) -o $(BLD)
obj:
	$(CC) ray_tracer.c $(FLAGS) $(INCDIR) $(LIBDIR) $(LIBS) -c
asm:
	$(CC) ray_tracer.c $(FLAGS) $(INCDIR) $(LIBDIR) $(LIBS) -S
clean:
	rm -f $(BLD)
	rm -f ray_tracer.o
	rm -f ray_tracer.s
run:
	$(BLD)
cleanup:
	clang-format ray_tracer.c > tmp.txt
	cat tmp.txt > ray_tracer.c
	rm tmp.txt
all:
	make cleanup
	make check
	make clean
	make
	make run
check:
	cppcheck --enable=all --inconclusive --std=posix --check-config --suppress=missingIncludeSystem ray_tracer.c
no-link:
	make clean
	make asm
	make obj

