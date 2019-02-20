#include "linha.h"

void mostrarLinha(Linha lin){
	char h[6];
    printf("\nCodigo: %d",lin.id);
    printf("\nCidade: %s", lin.cid);
	sprintf(h, "%02d:%02d",lin.hora.h, lin.hora.m);
    printf("\nHorário de partida: %s", h);
    printf("\nValor da passagem: %.2f R$\n", lin.vlr);
}