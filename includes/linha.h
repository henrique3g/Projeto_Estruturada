#ifndef LINHA_H
#define LINHA_H
// --- Bibliotecas do Sistema ---
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
// --- Variaveis auxiliares --- //
int cont_Lin;
int num_linhas;
Linha *lin;

// --- Funções para manipular Linhas --- //
Linha* carregarLinhas();

void mostrarLinha(Linha lin);

void listarLinhas();

void inserirLinha();

void removerLinha();

void alterarLinha();

int pesquisarLinha();

int pesquisaLin(char *cid, Hora h);

int pesquisarLinId(int id);

void consultarHorarios();

#endif
