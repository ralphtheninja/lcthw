# CPPFLAGS=-DNDEBUG
CFLAGS=-Wall -g -fsanitize=address
#CFLAGS=-Wall -g

all: ex1 ex2 ex3 ex4 ex7 ex8 ex9 ex10 ex11 ex12 ex13 ex14 ex15 ex16 ex17 ex18 ex19 getenv ex22_main ex23 ex24

ex22_main: ex22_main.c ex22.c ex22.h
	cc $(CPPFLAGS) $(CCFLAGS) -c -o ex22.o ex22.c
	cc $(CPPFLAGS) $(CCFLAGS) ex22_main.c ex22.o -o ex22_main

clean:
	rm -f ex[0-9] ex[0-9][0-9] getenv ex22_main
