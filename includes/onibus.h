#ifndef ONIBUS_H
#define ONIBUS_H
// --- Bibliotecas do Sistema ---
#include "func.h"
#include "linha.h"
#include "relatorio.h"

#define bdoni "bd/onibus.bin"		// Macro com o nome do arquivo de onibus
typedef struct {		// Estrutura Onibus
	int idLin;
	Data data;
	int ass[20];
}Onibus;

// --- Variaveis auxiliares ---
Onibus *oni;
int num_onibus;

// --- Funções para manipular Onibus --- //
Onibus* carregarOnibus();			// Carrega todos os onibus para a memoria

int mostrarAssentos(int o);			// Mostra os assentos do onibus passado por parametro

int pesquisarOnibus(int l, Data *d);// Pesquisa um onibus

void consultarAssentos();			// Consulta assentos disponivei em um onibus (MENU)

void iniciarAssentos();				// Inicia os assentos quando o onibus ainda não existe

int getTotReserva(Onibus o);		// Retorna o total dereservas feiras no onibus passado por parametro

void lerReserva();					// Ler reservas de um arquivo texto

#endif