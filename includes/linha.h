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
int cont_Lin;
int num_linhas;
Linha *lin;
Linha* carregarLinhas();

void mostrarLinha(Linha lin);

void listarLinhas();

void inserirLinha();

void removerLinha();

void alterarLinha();

int pesquisarLinha();

#endif
