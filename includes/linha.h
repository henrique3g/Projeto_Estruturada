#ifndef LINHA_H
#define LINHA_H
// --- Bibliotecas do Sistema ---
#include "func.h"
#include "menu.h"

#define bdlin "bd/linhas.bin"       // Macro com o nome do arquivo de linhas

typedef struct {        // Estrutura Linha
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

// --- Funções para manipular Linhas ---//
void carregarLinhas();                // Função q carrega todas as linhas para a memoria

void mostrarLinha(Linha lin);           // Mostra a linha passada por parametro

void listarLinhas();                    // Lista todas as linhas existentes    

void inserirLinha();                    // Insere uma linha

void removerLinha();                    // Remove uma linha caso não tenha onibus para essa linha

void alterarLinha();                    // Altera um linha

int pesquisarLinha();                   // Pesquisa uma linha

int pesquisarLinNome(char *cid, Hora h);// Pesquisa uma linha pelo nome e data

int pesquisarLinId(int id);             // Pesquisa uma linha pelo id

void consultarHorarios();               // Consulta horarios para uma determinada cidade

#endif
