#ifndef RELATORIO_H
#define RELATORIO_H
// --- Bibliotecas do Sistema ---
#include "func.h"
#include "onibus.h"

// --- Macro para tabulação em arquivo texto que ficou diferente Linux/Windows
#ifdef __unix__
    #define es "\t\t"
#elif defined(_WIN32) || defined(WIN32)
	#define es "\t" 
#endif

FILE *flog;				// Variavel para arquivo de log

void relArrecTela();	// relatorio de arrecadação na tela

void relArrecArq();		// Relatorio de arrecadação em arquivo

void relOcupTela();		// Relatorio deocupação na tela

void relOcupArq();		// Relatorio deocupação em arquivo

void logErro(char *s, char *msg);	// Escreve mensgens no arquivo de log

#endif