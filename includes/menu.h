#ifndef MENU_H
#define MENU_H
// --- Bibliotecas do Sistema ---
#include "func.h"
#include "linha.h"
#include "onibus.h"
#include "relatorio.h"

void menu();

void menuRel();

void opcao(int op);

void cabecalho(int i);

void printCabecalho(char *s);

void sair();

#endif