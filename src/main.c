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

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(){
	setlocale(LC_ALL, "");

	lin = carregarLinhas();
	oni = carregarOnibus();
	
	menu();
	return 0;
}