#ifndef MENU_H
#define MENU_H
// --- Bibliotecas do Sistema ---
#include "func.h"
#include "linha.h"
#include "onibus.h"
#include "relatorio.h"

// --- Funções de Menu ---
void menu();					// Exibe o menu principal

void menuRel();					// Exibe o menu de ralatorios

void opcao(int op);				// Trata a opção escolhida

void cabecalho(int i);			// Imprime um cabeçalho de acordo com o indice passado

void printCabecalho(char *s);	// Imprime um cabeçalho com a string passada

void sair();					// Função que sai do sistema e salva grava nos arquivos binarios

#endif