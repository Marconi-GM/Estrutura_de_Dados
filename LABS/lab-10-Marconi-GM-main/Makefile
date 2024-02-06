all: cozinha

cozinha: cozinha.o maxheap.o restaurante.o
	gcc cozinha.o maxheap.o restaurante.o -lm -o cozinha

cozinha.o: cozinha.c cozinha.h maxheap.h
	gcc -std=c99 -Wall -Werror -Wvla -c cozinha.c

restaurante.o: restaurante.c cozinha.h maxheap.h
	gcc -std=c99 -Wall -Werror -Wvla -c restaurante.c

maxheap.o: maxheap.c maxheap.h
	gcc -std=c99 -Wall -Werror -Wvla -c maxheap.c
