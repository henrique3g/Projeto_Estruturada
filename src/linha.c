#include "linha.h"

void mostrarLinha(Linha lin){
	char h[6];
    printf("Codigo: %d",lin.id);
    printf("\nCidade: %s", lin.cid);
	sprintf(h, "%02d:%02d",lin.hora.h, lin.hora.m);
    printf("\nHorário de partida: %s", h);
    printf("\nValor da passagem: R$ %.2f\n", lin.vlr);
}

Linha* carregarLinhas(){
    FILE *fp = fopen(bdlin, "rb");
    
    if(!fp){
        fp = fopen(bdlin, "wb");
		if(fp == NULL)	exit(1);
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

	l.id = cont_Lin+1;
	printf("Código: %d\n", l.id);
	lerString(l.cid, "Cidade: ");
	lerHora(&l.hora);
	printf("Valor da passagem: R$ ");
	scanf("%f", &l.vlr);
	clearBuf();
	
	cls();
	cabecalho(1);
	mostrarLinha(l);
	success("\n1-Salvar  ");
	danger("0-Cancelar\n");
	printf("Opção: ");
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
			danger("Opção invalida!\n");
			getchar();
			break;
	}
		
}

void removerLinha(){
	int l = pesquisarLinha();
	int op;
	if(l == -1){
		danger("Linha não encontrada!\n");
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
						warning("\nEssa linha não pode ser excluida pois possui registros!");
						getchar();
						return;
					}
				}
			}
		}
		success("\n1-Excluir  ");
		danger("0-Cancelar\n");
		printf("Opção: ");
		scanf("%d", &op);
		clearBuf();
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
			success("Linha removida com sucesso!");
			getchar();
			return;
		}else if(!op){
			return;
		}else{
			danger("Opção invalida!\n");
			getchar();
		}
	}

}

void alterarLinha(){
	int i = pesquisarLinha();
	int op;
	if(i == -1){
		danger("Linha não encontrada!\n");
		getchar();
		return;
	}
	Linha l = lin[i];
	do{	
		cls();
		cabecalho(3);
		mostrarLinha(l);
		printf("\n1-Cidade  2-Hora  3-Valor  ");
		success("4-Salvar  ");
		danger("0-Cancelar\n");
		printf("Opção: ");
		scanf("%d", &op);
		clearBuf();
		switch (op){
			case 1:
				lerString(l.cid, "Cidade: ");
				break;
			case 2:
				lerHora(&l.hora);
				break;
			case 3:
				printf("Valor: ");
				scanf("%f", &l.vlr);;
				break;
			case 4:
				lin[i] = l;
				success("Linha alterada com sucesso!");
				getchar();
				return;
			case 0:
				return;
			default:
				danger("Opção invalida!\n");
				getchar();
				break;
		}

	} while (1);
}

int pesquisarLinha(){
	Linha l;
	l.id = -1;
	char cid[MAX];
	lerString(cid, "Cidade ou Codigo: ");
	if(isNum(cid)){
		l.id = atoi(cid);
		return pesquisarLinId(l.id);
	}
	lerHora(&l.hora);
	return pesquisarLinNome(cid, l.hora);
}

void listarLinhas(){
	for(int i = 0; i < num_linhas; i++){
		mostrarLinha(lin[i]);
		printf("\n");
	}
	getchar();
}

void consultarHorarios(){
	char cid[MAX];
	int flag = 0;
	lerString(cid, "Cidade: ");
		
	for(int i = 0; i < num_linhas; i++){
		if(!strcmp(cid, lin[i].cid)){
			printf("%02d:%02d\tR$ %.2f\n",lin[i].hora.h,lin[i].hora.m,lin[i].vlr);
			flag = 1;
		}
	}
	if(!flag){
		warning("Nenhuma linha encontrada!");
	}
	getchar();
}

int pesquisarLinNome(char *cid, Hora h){
    
    for(int i = 0; i < num_linhas; i++){
        if(!strcmp(cid, lin[i].cid)){
            if((h.h == lin[i].hora.h && h.m == lin[i].hora.m)){
                return i;
            }
        }
        
    }
    
    return -1;
}

int pesquisarLinId(int id){
	for(int i = 0; i < num_linhas; i++){
		if(id == lin[i].id){
			return i;
		}
	}
	return -1;
}