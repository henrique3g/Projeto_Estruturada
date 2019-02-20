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

long int num_onibus;

Onibus* carregarOnibus();

#endif