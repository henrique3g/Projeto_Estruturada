#include "relatorio.h"

void relArrecTela(){		// imprime o relatorio de arrecadação mensal na tela
	float valor = 0, total = 0;
	int f = 0;
		
	Data d = getData();
	cls();
	printf("/////////////////////////////////////////////////\n");
	printf("//                                             //\n");
	printf("//        Relatório Arrecadação Mensal         //\n");
	printf("//                                             //\n");
	printf("//                 Emissão: %02d/%02d/%04d         //\n", d.dia, d.mes, d.ano);
	printf("/////////////////////////////////////////////////\n");
	printf("+-----------------------------------------------+\n");
	printf("|%-29s|%7s|%s|\n","Cidade", "Horário", "Total/Mês");
	printf("+-----------------------------+-------+---------+\n");
	for(int i = 0; i < num_linhas; i++){
		for(int j = 0; j < num_onibus; j++){
			if(oni[j].idLin == lin[i].id){
				if(oni[j].data.mes == d.mes && oni[j].data.ano == d.ano){
					valor += lin[i].vlr * getTotReserva(oni[j]);
					f = 1;
				}
			}
		}
		if(f == 1){
			printf("|%-29s| %02d:%02d | %8.2f|\n", lin[i].cid, lin[i].hora.h, lin[i].hora.m, valor);
			f = 0;
		}
		total += valor;
		valor = 0;
	}
	printf("+-----------------------------------------------+\n");
	printf("|\033[32mTotal                                %10.2f\033[m|\n", total);
	printf("+-----------------------------------------------+\n");
	pause();

}

void relArrecArq(){		// imprime o relatorio de arrecadação mensal em arquivo
	float valor = 0, total = 0;
	int f = 0;
	char arq[100];
	
	Data d = getData();
	sprintf(arq, "relatorios/relatorio de vendas do mes %d emitido %02d-%02d-%04d.txt", d.mes,d.dia , d.mes, d.ano);
	
	FILE *frel = fopen(arq, "w");
	fprintf(frel, "/////////////////////////////////////////////////\n");
	fprintf(frel, "//                                             //\n");
	fprintf(frel, "//        Relatório Arrecadação Mensal         //\n");
	fprintf(frel, "//                                             //\n");
	fprintf(frel, "//                 Emissão: %02d/%02d/%04d         //\n", d.dia, d.mes, d.ano);
	fprintf(frel, "/////////////////////////////////////////////////\n");
	fprintf(frel, "+-----------------------------+-------+---------+\n");
	fprintf(frel, "|%-29s|%7s|%s|\n","Cidade", "Horário", "Total/Mês");
	fprintf(frel, "+-----------------------------+-------+---------+\n");
	for(int i = 0; i < num_linhas; i++){
		for(int j = 0; j < num_onibus; j++){
			if(oni[j].idLin == lin[i].id){
				if(oni[j].data.mes == d.mes && oni[j].data.ano == d.ano){
					valor += lin[i].vlr * getTotReserva(oni[j]);
					f = 1;
				}
			}
		}
		if(f == 1){
			fprintf(frel, "|%-29s| %02d:%02d | %8.2f|\n", lin[i].cid, lin[i].hora.h, lin[i].hora.m, valor);
			f = 0;
		}
		total += valor;
		valor = 0;
	}
	
		
	
	fprintf(frel,"+-----------------------------------------------+\n");
	fprintf(frel,"|Total                                %10.2f|\n", total);
	fprintf(frel,"+-----------------------------------------------+\n");


	
	fclose(frel);
	success("Relatório gerado com sucesso!");
	pause();
	sprintf(arq, "\"relatorios\\relatorio de vendas do mes %d emitido %02d-%02d-%04d.txt\"", d.mes,d.dia, d.mes, d.ano);
	printf("Feche o arquivo aberto para continuar!\n");
	system(arq);

}

void relOcupTela(){			// imprime o relatorio de ocupação por dia da semana mensal na tela
	int tot[7];
	int soma=0;
	for(int i = 0; i < 7; i++) tot[i] = 0;
	int f = 0;
	char str[60];
	
	Data d = getData();
	cls();
	printf("//////////////////////////////////////////////////////\n");
	printf("//                                                  //\n");
	printf("//     Relatório de ocupação por dia da semana      //\n");
	printf("//                                                  //\n");
	printf("//                          Emissão: %02d/%02d/%04d     //\n", d.dia, d.mes, d.ano);
	printf("//////////////////////////////////////////////////////\n");
	printf("+----------------------------------------------------+\n");
	for(int i = 0; i < num_linhas; i++){
		for(int j = 0; j < num_onibus; j++){
			if(oni[j].idLin == lin[i].id){
				if(oni[j].data.mes == d.mes && oni[j].data.ano == d.ano){
					tot[getDiaSemana(oni[j].data)] += getTotReserva(oni[j]);
					soma += getTotReserva(oni[j]);
					f = 1;
				}
			}
		}
					
		if(f == 1){
			sprintf(str, "|%s, %02d:%02d , Total no mês = %02d", lin[i].cid, lin[i].hora.h, lin[i].hora.m, soma);
			printf("%-54s|\n",str);
			printf("|Dom\tSeg\tTer\tQua\tQui\tSex\tSab  |\n|");
			for(int k = 0; k < 7; k++)
				printf("%s%02d\033[m/80%c",tot[k]<20?"\033[31m":tot[k]>=20&&tot[k]<=50?"\033[33m":"\033[32m",tot[k], k == 6?'|':'\t');
			printf("\n+----------------------------------------------------+\n");
			for(int k = 0; k < 7; k++) tot[k] = 0;
			f = 0;
			soma = 0;
		}
	}
	pause();
}

void relOcupArq(){		// imprime o relatorio de ocupação por dia da semana mensal em arquivo
	int tot[7];
	int soma=0;
	for(int i = 0; i < 7; i++) tot[i] = 0;
	int f = 0;
	char str[60];
	
	char arq[100];
	Data d = getData();
	sprintf(arq, "relatorios/relatorio de ocupacao do mes %d emitido %02d-%02d-%04d.txt", d.mes,d.dia, d.mes, d.ano);
	FILE *frel = fopen(arq, "w");
	fprintf(frel, "//////////////////////////////////////////////////////\n");
	fprintf(frel, "//                                                  //\n");
	fprintf(frel, "//     Relatório de ocupação por dia da semana      //\n");
	fprintf(frel, "//                                                  //\n");
	fprintf(frel, "//                         Emissão: %02d/%02d/%04d      //\n", d.dia, d.mes, d.ano);
	fprintf(frel, "//////////////////////////////////////////////////////\n");
	fprintf(frel, "+----------------------------------------------------+\n");
	for(int i = 0; i < num_linhas; i++){
		for(int j = 0; j < num_onibus; j++){
			if(oni[j].idLin == lin[i].id){
				if(oni[j].data.mes == d.mes && oni[j].data.ano == d.ano){
					tot[getDiaSemana(oni[j].data)] += getTotReserva(oni[j]);
					soma += getTotReserva(oni[j]);
					f = 1;
				}
			}
		}
					
		if(f == 1){
			sprintf(str, "|%s, %02d:%02d , Total no mês = %02d", lin[i].cid, lin[i].hora.h, lin[i].hora.m, soma);
			fprintf(frel, "%-54s|\n",str);
			fprintf(frel, "|Dom\tSeg%sTer%sQua%sQui%sSex%sSab  |\n|",es,es,es,es,es);
			for(int k = 0; k < 7; k++)
				fprintf(frel, "%02d/80%c",tot[k], k == 6?'|':'\t');
			fprintf(frel, "\n+----------------------------------------------------+\n");
			for(int k = 0; k < 7; k++) tot[k] = 0;
			f = 0;
			soma = 0;
		}
	}
	
	fclose(frel);
	success("Relatório gerado com sucesso!");
	pause();
	sprintf(arq, "\"relatorios\\relatorio de ocupacao do mes %d emitido %02d-%02d-%04d.txt\"", d.mes, d.dia, d.mes, d.ano);
	printf("Feche o arquivo aberto para continuar!\n");
	system(arq);
}

void logErro(char *s, char *msg){		// grava a mesagem de log no arquivo e imprime na tela
	if(!strcmp("Reserva realizada!",msg)){		// se conseguir reservar imprime em verde na tela
		printf("\033[32mem \"%s\": %s\n\033[m", s, msg);

	}else{		// se não conseguir reservar imprime em vermelho na tela
		printf("\033[31mem \"%s\": %s\n\033[m", s, msg);
	}
	fprintf(flog, "em \"%s\": %s\n", s, msg);		// grava no aruivo
	
}