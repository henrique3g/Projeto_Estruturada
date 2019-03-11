#ifndef ONIBUS_H
#define ONIBUS_H
// --- Bibliotecas do Sistema ---
#include "func.h"
#include "linha.h"
#include "relatorio.h"

#define bdoni "bd/onibus.bin"
typedef struct {
	int id;
	int idLin;
	Data data;
	int ass[20];
}Onibus;
// --- Variaveis auxiliares ---
Onibus *oni;
int num_onibus;
int cont_oni;
// --- Funções para manipular Onibus --- //
Onibus* carregarOnibus();

int mostrarAssentos(int o);

int pesquisarOnibus(int l, Data *d);

void consultarAssentos();

void iniciarAssentos();

int getTotReserva(Onibus o);

int pesquisaOni(int l, Data *d);

void lerReserva();
#endif