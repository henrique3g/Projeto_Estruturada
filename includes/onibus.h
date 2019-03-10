#ifndef ONIBUS_H
#define ONIBUS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "linha.h"
#include "func.h"
#include "relatorio.h"

#define bdoni "bd/onibus.bin"
typedef struct {
	int id;
	int idLin;
	Data data;
	int ass[20];
}Onibus;

Onibus *oni;
int num_onibus;
int cont_oni;

Onibus* carregarOnibus();

int mostrarAssentos(int o);

int pesquisarOnibus(int l, Data *d);

void consultarAssentos();

void iniciarAssentos();

int getTotReserva(Onibus o);

int pesquisaOni(int l, Data *d);

void lerReserva();
#endif