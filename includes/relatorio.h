#ifndef RELATORIO_H
#define RELATORIO_H
// --- Bibliotecas do Sistema ---
#include "func.h"
#include "onibus.h"

#ifdef __unix__
    #define es "\t\t"
#elif defined(_WIN32) || defined(WIN32)
	#define es "\t" 
#endif

FILE *flog;

void relArrecTela();

void relArrecArq();

void relOcupTela();

void relOcupArq();

void logErro(char *s, char *msg);

#endif