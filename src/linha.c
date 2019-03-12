#include "linha.h"

void mostrarLinha(Linha lin){		// imprime na tela as invormção da linha
	char h[6];
    printf("Código: %d",lin.id);
    printf("\nCidade: %s", lin.cid);
	sprintf(h, "%02d:%02d",lin.hora.h, lin.hora.m);
    printf("\nHorário de partida: %s", h);
    printf("\nValor da passagem: R$ %.2f\n", lin.vlr);
}

void mostrarLinhaAtivo(Linha lin){	// Imprime na tela as informações da linha e se ela esta ativa ou não
	mostrarLinha(lin);
	if(lin.ativo){		// se esta ativo imprime em verde 
		success("Ativo\n");
	}else{
		danger("Desativado\n");	// se esta inativo imprime em vermelho
	}
}
void carregarLinhas(){		// carrega a quantidade de linhas e todas as linhas para o vetor 'lin'
    FILE *fp = fopen(bdlin, "rb");		// abre para leitura 'linhas.bin'
    int err = 0;
    if(!fp){	// se não existir o arquivo inicia o vetor do zero
		cont_Lin = 0;	// zera o contador de condigo
        num_linhas = 0;	// zera o numero de linhas
    }else{
        if(fread(&num_linhas, sizeof(int), 1, fp)){ // verifica se conseguiu ler o numero de lihas
			if(fread(&cont_Lin, sizeof(int), 1, fp)){	// verifica se conseguir ler o contados de codigos
				if(num_linhas){	//verifica se tem alguma linha se tiver faz a leitura
					lin = malloc(sizeof(Linha)*num_linhas);	// aloca memoria
					if(fread(lin, sizeof(Linha), num_linhas, fp)){	// ler todas as linhas
						return;
					}else{	
						err = 1;
					}
				}else{
					fclose(fp);
					return;
				}
			}else{
				err = 1;
			}
        }else{
			err = 1;
		}
		if(err){	// se char aq e err for 1 sai do sistema
			danger("Erro ao ler arquivo");
			pause();
			exit(1);
		}
    }
    
}

void inserirLinha(){		// insere linhas no 'linhas.bin'
	int op;
	Linha l;	// criar uma variavel linha auxiliar

	// faz a leitura dos dados da linha
	l.id = cont_Lin+1;
	printf("Código: %d\n", l.id);
	lerString(l.cid, "Cidade: ");
	lerHora(&l.hora);
	printf("Valor da passagem: R$ ");
	scanf("%f", &l.vlr);
	clearBuf();

	l.ativo = 1;	// deixa linha ativa
	
	cls();
	cabecalho(1);	//imprime cabeçalho
	mostrarLinha(l);	// imprime linha
	// dar a opção em salvar ou não
	success("\n1-Salvar  ");
	danger("0-Cancelar\n");
	printf("Opção: ");
	scanf("%d", &op);
	clearBuf();
	// trata a opção se for 1 salva se for 0 cancela 
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
			pause();
			break;
	}
		
}

void removerLinha(){  // remove uma linha
	int l = pesquisarLinha();	// pesquisa por uma linha
	int op;
	if(l == -1){ // verifica se alinha existe
		danger("Linha não encontrada!\n");
		pause();
		return;
	}
	while(1){ 
		cls();
		cabecalho(2); //imprime cabeçalho
		mostrarLinhaAtivo(lin[l]);	// mostra linha
		for(int i = 0; i < num_onibus; i++){		// verifica se a linha não possui onibus iniciados
			if(oni[i].idLin == lin[l].id){		// se achar algum onibus verifica se tem assentos reservados
				for(int j = 0; j < 20; j++){
					if(oni[i].ass[j] == -1){	// se tiver assentos reservados não permite cancelar
						warning("\nEssa linha não pode ser excluida pois possui registros!");
						pause();
						return;
					}
				}
			}
		}
		// menu de opção 1 excluir e 0 cancelar
		success("\n1-Excluir  ");
		danger("0-Cancelar\n");
		printf("Opção: ");
		scanf("%d", &op);
		clearBuf();
		if(op == 1){ // remove a linha
			for(int i = 0; i < num_onibus; i++){	// procura por onibus iniciados sem reserva para removelos
				if(oni[i].idLin == lin[l].id){
					oni[i] = oni[num_onibus-1];
					num_onibus--;
					oni = realloc(oni, sizeof(Onibus)*num_onibus);
				}
			}
			lin[l] = lin[num_linhas-1];	// remove linha
			num_linhas--;
			lin = realloc(lin, sizeof(Linha)*num_linhas);
			success("Linha removida com sucesso!");
			pause();
			return;
		}else if(!op){	// cancela
			return;
		}else{
			danger("Opção invalida!\n");
			pause();
		}
	}

}

void alterarLinha(){	// altera uma linha
	int i = pesquisarLinha();	// pesquisa pela linha
	int op;
	if(i == -1){	// verifica se a linha existe
		danger("Linha não encontrada!\n");
		pause();
		return;
	}
	Linha l = lin[i]; // criar variavel Linha auxiliar
	do{	
		cls(); // limpa tela
		cabecalho(3);	// imprime o cabeçalho
		mostrarLinhaAtivo(l);	// mostra todas as informações da linha
		// menu de opções
		printf("\n1-Cidade  2-Hora  3-Valor  ");
		success("4-Salvar  ");
		if(l.ativo){	// se a linha esta ativa oferece opção de desativar
			warning("5-Desativar  ");
		}else{		// se a linha estiver inativa oferece opção de ativar
			warning("5-Ativar  ");
		}
		danger("0-Cancelar\n");
		printf("Opção: ");
		scanf("%d", &op);
		clearBuf();
		// trata a opção 
		switch (op){
			case 1:	// altera nome cidade da linha
				lerString(l.cid, "Cidade: ");
				break;
			case 2:	// altera hora linha
				lerHora(&l.hora);
				break;
			case 3:	// altera valor da linha
				printf("Valor: ");
				scanf("%f", &l.vlr);;
				break;
			case 4:	// salva alterações
				lin[i] = l;
				success("Linha alterada com sucesso!");
				pause();
				return;
			case 5:	// ativa ou desativa linha
				l.ativo = !l.ativo;
				break;
			case 0:	// cancela
				return;
			default:
				danger("Opção invalida!\n");
				pause();
				break;
		}

	} while (1);
}

int pesquisarLinha(){	// pesquisa por uma linha
	Linha l;
	l.id = -1;
	char cid[MAX];
	lerString(cid, "Cidade ou Código: "); // ler o nome ou o codigo da cidade
	if(isNum(cid)){	// se for um codigo pesquisa por codigo
		l.id = atoi(cid);
		return pesquisarLinId(l.id);
	}
	// se for nome pesquisa pelo nome e data
	lerHora(&l.hora);
	return pesquisarLinNome(cid, l.hora);
}

void listarLinhas(){	// lista todas as linhas existentes
	for(int i = 0; i < num_linhas; i++){
		mostrarLinhaAtivo(lin[i]);
		printf("\n");
	}
	pause();
}

void consultarHorarios(){		// consulta horarios disponiveis para um cidade
	char cid[MAX];
	int flag = 0;
	lerString(cid, "Cidade: ");
		
	for(int i = 0; i < num_linhas; i++){	// procura pela cidade
		if(!strcmp(cid, lin[i].cid) && lin[i].ativo){	//se achar imprime as informações da linha
			printf("%02d:%02d\tR$ %.2f\n",lin[i].hora.h,lin[i].hora.m,lin[i].vlr);
			flag = 1;
		}
	}
	if(!flag){	
		warning("Nenhuma linha encontrada!");
	}
	pause();
}

int pesquisarLinNome(char *cid, Hora h){	// pesquisa uma linha pelo nome e data
    
    for(int i = 0; i < num_linhas; i++){
        if(!strcmp(cid, lin[i].cid)){
            if((h.h == lin[i].hora.h && h.m == lin[i].hora.m)){
                return i;
            }
        }
        
    }
    
    return -1;
}

int pesquisarLinId(int id){	// pesquisa uma linha pelo if
	for(int i = 0; i < num_linhas; i++){
		if(id == lin[i].id){
			return i;
		}
	}
	return -1;
}