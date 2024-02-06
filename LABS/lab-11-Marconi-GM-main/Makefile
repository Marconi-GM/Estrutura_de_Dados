all: halloween

halloween: halloween.o sistema.o
	gcc halloween.o sistema.o -lm -o halloween

halloween.o: halloween.c sistema.c sistema.h
	gcc -Wall -Werror -Wvla -std=c99 -c halloween.c

sistema.o: sistema.c sistema.h
	gcc -Wall -Werror -Wvla -std=c99 -c sistema.c