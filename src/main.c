/* ==============================================================
//  	INSTITUTO FEDEREAL DO SERTÃO PERNAMBUCANO                                            
// ==============================================================
//  -------------------------------------------------------------
//  - Sistema para controlar os assentos disponíveis nos Ônibus -
//  -------------------------------------------------------------
//  - Autores: João Henrique, Antonio Emannuel, Vinicius Luiz   -
//  - Data: 01/03/2019                                          -
//  -----------------------------------------------------------*/

/***************************************************
 * Bibliotecas                                     *
 * ************************************************/
#include <locale.h>		// biblioteca para definir o local
#include "func.h"
#include "menu.h"


int main(){
	setlocale(LC_ALL, "");	// passa as datas , simbolos de moeda e acentuações

	carregarLinhas();	// carrega todas as linhas do 'linhas.bin' para a memoria ram
	carregarOnibus();	// carrega todas os onibus do 'onibus.bin' para a memoria ram
	
	menu();	// chama a função menu
	return 0;
}