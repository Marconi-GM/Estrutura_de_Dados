all: expressoes

expressoes: expressoes.o arvorebinaria.o funcoes_expressoes.o
	gcc expressoes.o arvorebinaria.o funcoes_expressoes.o -lm -o expressoes

expressoes.o: expressoes.c expressoes.h
	gcc -Wall -Werror -Wvla -std=c99 -c expressoes.c

arvorebinaria.o: arvorebinaria.c arvorebinaria.h
	gcc -Wall -Werror -Wvla -std=c99 -c arvorebinaria.c

funcoes_expressoes.o: funcoes_expressoes.c funcoes_expressoes.h
	gcc -Wall -Werror -Wvla -std=c99 -c funcoes_expressoes.c