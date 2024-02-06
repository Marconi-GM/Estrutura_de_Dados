all: dracarys

dracarys: dracarys.o arvorerubronegra.o johncc.o
	gcc dracarys.o arvorerubronegra.o johncc.o -lm -o dracarys

dracarys.o: dracarys.c dracarys.h
	gcc -Wall -Werror -Wvla -std=c99 -c dracarys.c

arvorerubronegra.o: arvorerubronegra.c arvorerubronegra.h johncc.h
	gcc -Wall -Werror -Wvla -std=c99 -c arvorerubronegra.c

johncc.o: johncc.c johncc.h
	gcc -Wall -Werror -Wvla -std=c99 -c johncc.c