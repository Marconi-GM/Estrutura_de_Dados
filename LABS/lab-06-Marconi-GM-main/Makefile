all: livros

livros: livros.o funcoes_para_livros.o
	gcc livros.o funcoes_para_livros.o -lm -o livros

livros.o: livros.c livros.h
	gcc -Wall -Werror -Wvla -std=c99 -c livros.c

funcoes_para_livros.o: funcoes_para_livros.c livros.h
	gcc -Wall -Werror -Wvla -std=c99 -c funcoes_para_livros.c