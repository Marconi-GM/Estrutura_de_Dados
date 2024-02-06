#ifndef DRACARYS_H
#define DRACARYS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 200
#define MIN 10

typedef struct variavel variavel;

// variavel, contendo um tipo (char , double, int) e um simbolo (seu nome)
struct variavel{

    char tipo[MIN];
    char simbolo[MAX];

};

#endif 
