#include "linha.h"

void mostrarLinha(Linha lin){
	char h[6];
    printf("\nCodigo: %d",lin.id);
    printf("\nCidade: %s", lin.cid);
	sprintf(h, "%02d:%02d",lin.hora.h, lin.hora.m);
    printf("\nHorário de partida: %s", h);
    printf("\nValor da passagem: %.2f R$\n", lin.vlr);
}

Linha* carregarLinhas(){
    FILE *fp = fopen(bdlin, "rb");
    
    if(!fp){
        fp = fopen(bdlin, "wb");
		cont_Lin = 0;
        num_linhas = 0;
    }else{
        if(fread(&num_linhas, sizeof(int), 1, fp)){
			if(fread(&cont_Lin, sizeof(int), 1, fp)){
				if(num_linhas){
					lin = malloc(sizeof(Linha)*num_linhas);
					if(fread(lin, sizeof(Linha), num_linhas, fp)){
						fclose(fp);
						return lin;
					}

				}
			}
        }
    }
    fclose(fp);
    return NULL;
}

void inserirLinha(){
	int op;
	Linha l;

	cabecalho(1);
	l.id = cont_Lin+1;
	printf("\nCódigo: %d\n", l.id);
	printf("Cidade: ");
	lerString(l.cid);
	printf("Horário de partida: ");
	scanf("%d:%d", &l.hora.h, &l.hora.m);
	clearBuf();
	while(!validaHora(l.hora)){
		printf("Erro! Hora invalida!\n");
		printf("Horário de partida: ");
		scanf("%d:%d", &l.hora.h, &l.hora.m);
		clearBuf();
	}
	printf("Valor da passagem: ");
	scanf("%f", &l.vlr);
	clearBuf();
	
	cls();
	cabecalho(1);
	mostrarLinha(l);
	printf("\n1-Salvar  0-Cancelar\nOpção: ");
	scanf("%d", &op);
	clearBuf();
	switch (op){
		case 1:
			lin = realloc(lin, sizeof(Linha)*(num_linhas+1));
			lin[num_linhas] = l;
			num_linhas++;
			cont_Lin++;
			break;
		case 0:
			break;
		default:
			printf("Opção invalida!\n");
			getchar();
			break;
	}
		
}

void removerLinha(){
	cabecalho(2);
	int l = pesquisarLinha();
	int op;
	if(l == -1){
		printf("Linha não encontrada!\n");
		getchar();
		return;
	}
	while(1){
		cls();
		cabecalho(2);
		mostrarLinha(lin[l]);
		for(int i = 0; i < num_onibus; i++){
			if(oni[i].idLin == lin[l].id){
				for(int j = 0; j < 20; j++){
					if(oni[i].ass[j] == -1){
						printf("\nEssa linha não pode ser excluida pois possui registros!");
						getchar();
						return;
					}
				}
			}
		}
		printf("\n1-Excluir  0-Cancelar\nOpção: ");
		scanf("%d", &op);
		if(op == 1){
			for(int i = 0; i < num_onibus; i++){
				if(oni[i].idLin == lin[l].id){
					oni[i] = oni[num_onibus-1];
					num_onibus--;
					oni = realloc(oni, sizeof(Onibus)*num_onibus);
				}
			}
			lin[l] = lin[num_linhas-1];
			num_linhas--;
			lin = realloc(lin, sizeof(Linha)*num_linhas);
			return;
		}else if(!op){
			return;
		}else{
			printf("Opção invalida!\n");
			getchar();
		}
	}

}

void alterarLinha(){
	int i = pesquisarLinha();
	int op;
	if(i == -1){
		printf("Linha não encontrada!\n");
		getchar();
		return;
	}
	Linha l = lin[i];
	do{	
		cls();
		cabecalho(3);
		mostrarLinha(l);
		printf("\n1-Cidade  2-Hora  3-Valor  4-Salvar 0-Cancelar\nOpção: ");
		scanf("%d", &op);
		clearBuf();
		switch (op){
			case 1:
				printf("Cidade: ");
				lerString(l.cid);
				break;
			case 2:
				printf("Horário de partida: ");
				scanf("%d:%d", &l.hora.h, &l.hora.m);
				while(!validaHora(l.hora)){
					printf("Erro! Hora invalida!\n");
					printf("Horário de partida: ");
					scanf("%d:%d", &l.hora.h, &l.hora.m);
					clearBuf();
				}
				break;
			case 3:
				printf("Valor: ");
				scanf("%f", &l.vlr);;
				break;
			case 4:
				lin[i] = l;
				return;
			case 0:
				return;
			default:
				printf("Opção invalida!\n");
				getchar();
				break;
		}

	} while (1);
}

int pesquisarLinha(){
	Linha l;
	l.id = -1;
	char cid[MAX];
	printf("\nCidade ou Codigo: ");
	lerString(cid);
	if(isNum(cid)){
		l.id = atoi(cid);
	}else{
		printf("Horário de partida: ");
		scanf("%d:%d", &l.hora.h, &l.hora.m);
		clearBuf();
		while(!validaHora(l.hora)){
			printf("Erro! Hora invalida!\n");
			printf("Horário de partida: ");
			scanf("%d:%d", &l.hora.h, &l.hora.m);
			clearBuf();
		}
	}
	for(int i = 0; i < num_linhas; i++){
		if(l.id != -1){
			if(l.id == lin[i].id){
				return i;
			}
		}else{
			if(!strcmp(cid, lin[i].cid)){
				if(lin[i].hora.h == l.hora.h && lin[i].hora.m == l.hora.m)
					return i;
			}
		}
		
	}
	return -1;
}

void listarLinhas(){
	cabecalho(4);
	for(int i = 0; i < num_linhas; i++){
		mostrarLinha(lin[i]);
	}
	getchar();
}

void consultarHorarios(){
	
	char cid[MAX];
	printf("\nCidade: ");
	lerString(cid);
		
	
	for(int i = 0; i < num_linhas; i++){
		
		if(!strcmp(cid, lin[i].cid)){
			printf("%02d:%02d\t%.2f\n",lin[i].hora.h,lin[i].hora.m,lin[i].vlr);
		}
		
	}
	getchar();
}

int pesquisaLin(char *cid, Hora h){
    
    for(int i = 0; i < num_linhas; i++){
        if(!strcmp(cid, lin[i].cid)){
            if((h.h == lin[i].hora.h && h.m == lin[i].hora.m)){
                return i;
            }
        }
        
    }
    
    return -1;
}