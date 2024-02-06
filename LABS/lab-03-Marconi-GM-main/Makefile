all: golfe

golfe: golfe.o partida.o circuito.o
	gcc golfe.o partida.o circuito.o -lm -o golfe

golfe.o: golfe.c circuito.h partida.h
	gcc -Wvla -Werror -Wall -std=c99 -c golfe.c

circuito.o: circuito.c circuito.h
	gcc -Wvla -Werror -Wall -std=c99 -c circuito.c

partida.o: partida.c partida.h
	gcc -Wvla -Werror -Wall -std=c99 -c partida.c
