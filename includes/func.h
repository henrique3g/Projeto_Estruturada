#ifndef FUNC_H
#define FUNC_H
// --- Bibliotecas do Sistema ---
#include <stdio.h>		// Entrada e saída
#include <stdlib.h>		// Funções gerais do sistema
#include <string.h>		// Manipular Strings
#include <ctype.h>		// Manipular Caracteres
#include <time.h>		// Manipular Datas e Horas

#define MAX 30		// Macro utilizada para padronizar o tamanho maximo de string padrão

typedef struct {		// Estrutura de data
	int dia;
	int mes;
	int ano;
}Data;


typedef struct {		// Estrura de hora
    int h;
    int m;
} Hora;
// --- Funções auxiliares --- //
void cls();					// Limpar tela

void clearBuf();			// Limpar buffer do teclado

int isPar(int n);			// Verifica se um número é par

void pause();				// Pausa o programa

// --- Funções de String ---
void lerString(char *s, char *msg);	// Faz a leitura de uma string

void rmvLn(char *s);		// Remove o '\n' do final de uma string

void toUpperCase(char *s);	// Deixa toda primeira letra com caixa alta

void trim(char *s);			// Remove espaços no inicio e fim da string

int isNum(char *s);			// Verifica se uma String é um número


// --- Funções de Data ---
Data getData();				// Retorna a data atual do sistema

void lerData(Data *d);		// Lê uma data do usuário

int validaData(Data d);		// Valida uma data

int diffDate(Data final);	// Retorna a diferença de dias entre a data passada por parametro e a data atual

int getDiaSemana(Data d);	// Retorna qual o dia da semana da data passada por parametro


// --- Funções de Hora ---
Hora getHora();				// Retorna a hora atual do sistema

int validaHora(Hora h);		// Valida hora

void lerHora(Hora *h);		// Lê um horario do usuário


//--- Funções de cores ---
void danger(char *texto);	// Printa um texto em vermelho

void success(char *texto);	// Printa um texto em verde

void warning(char *texto);	// Printa um texto em amarelo

#endif
