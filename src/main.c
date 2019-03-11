/* ==============================================================
//  	INSTITUTO FEDEREAL DO SERTÃO PERNAMBUCANO                                            
// ==============================================================
//  -------------------------------------------------------------
//  - Sistema para controlar os assentos disponíveis nos Ônibus -
//  -------------------------------------------------------------
//  - Autores: João Henrique, Antonio Emannuel, Vinicius Luiz   -
//  - Data: 02/02/2019                                          -
//  -----------------------------------------------------------*/

/***************************************************
 * Bibliotecas                                     *
 * ************************************************/
#include <locale.h>
#include "func.h"
#include "menu.h"


int main(){
	setlocale(LC_ALL, "");

	lin = carregarLinhas();
	oni = carregarOnibus();
	
	menu();
	return 0;
}