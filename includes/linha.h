#ifndef LINHA_H
#define LINHA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "func.h"
#include "menu.h"

#define bdlin "bd/linhas.bin"

typedef struct {
    int id;
    char cid[30];
    Hora hora;
    float vlr;
    int ativo;
} Linha;

long int num_linhas;

Linha* carregarLinhas();

void mostrarLinhas(Linha lin);

#endif
