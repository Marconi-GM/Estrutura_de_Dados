all: batmemory

batmemory: batmemory.o funcoes_auxiliares.o bat_funcoes.o
	gcc batmemory.o funcoes_auxiliares.o bat_funcoes.o -lm -o batmemory

batmemory.o: batmemory.c batmemory.h
	gcc -std=c99 -Wall -Werror -Wvla -c batmemory.c

funcoes_auxiliares.o: funcoes_auxiliares.c batmemory.h
	gcc -std=c99 -Wall -Werror -Wvla -c funcoes_auxiliares.c

bat_funcoes.o: bat_funcoes.c batmemory.h
	gcc -std=c99 -Wall -Werror -Wvla -c bat_funcoes.c