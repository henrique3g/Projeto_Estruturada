#include "menu.h"

void menu(){        // imprime o menu principal e ler a opção
    int op;
    do{
        op = -1;
        cabecalho(0);
        printf("1 - Inserir linha\n");
        printf("2 - Remover linha\n");
        printf("3 - Alterar linha\n");
        printf("4 - Listar linhas\n");
        printf("5 - Consultar horários\n");
        printf("6 - Consultar assentos disponível\n");
        printf("7 - Relatórios\n");
        printf("8 - Ler reservas de arquivos texto\n");
        danger("0 - Sair\n");
        printf("OPÇÃO: ");
        scanf("%d", &op);
        clearBuf();
        opcao(op);
    }while(op != 0);
}

void opcao(int op){     // trata a opção escolhida e chama a função e i cabeçalho correspondente
    switch (op){
        case 1:
            cabecalho(1);
            inserirLinha();
            break;
        case 2:
            cabecalho(2);
            removerLinha();
            break;
        case 3:
            cabecalho(3);
            alterarLinha();
            break;
        case 4:
            cabecalho(4);
            listarLinhas();
            break;
        case 5:
            cabecalho(5);
            consultarHorarios();
            break;
        case 6:
            cabecalho(6);
            consultarAssentos();
            break;
        case 7:
            cabecalho(7);
            menuRel();
            break;
        case 8:
            cabecalho(8);
            lerReserva();
            break;
        case 0:
            sair();
            break;
        default:
            printf("Opção Invalida!");
            pause();
            break;
    }
}

void menuRel(){     // imprime o menu de ralatorios
	int op;
    printf("1 - Total arrecadado (tela)\n");
    printf("2 - Total arrecadado (arquivo)\n");
    printf("3 - Ocupação percentual média (tela)\n");
    printf("4 - Ocupação percentual média (arquivo)\n");
    danger("0 - Voltar\n");
	printf("OPÇÃO: ");
    scanf("%d", &op);
    clearBuf();
    // trata a opção escolhida
    if(op == 1){
		relArrecTela();
	}else if(op == 2){
		relArrecArq();
	}else if(op == 3){
        relOcupTela();
	}else if(op == 4){
        relOcupArq();
	}
}

void cabecalho(int i){      // imprime os cabeçalhos de acordo com 'i'
	if(i == 0){
		printCabecalho("Menu");
    }else if(i == 1){
		printCabecalho("Cadastrar Linha");
	}else if(i == 2){
		printCabecalho("Remover Linha");
	}else if(i == 3){
		printCabecalho("Alterar Linha");
	}else if(i == 4){
		printCabecalho("Listar Linha");
	}else if(i == 5){
		printCabecalho("Consultar Horários");
	}else if(i == 6){
		printCabecalho("Consultar Assentos");
	}else if(i == 7){
		printCabecalho("Relatórios");
	}else if(i == 8){
		printCabecalho("Ler reservas de arquivo texto");
    }
}

void printCabecalho(char *s){   // função q imprime uma cabeçalho com o texto passado
	cls();
	int t = (int)strlen(s);
	int sp = (49/2) - (t/2);
	printf("/////////////////////////////////////////////////////\n");
    printf("//                                                 //\n//");
	for(int i = 0; i < sp; i++){
		printf(" ");
	}
	printf("%s", s);
	sp = (isPar(t)? (sp+1):(sp));
	for(int i = 0; i < sp; i++){
		printf(" ");
	}
    printf("//\n//                                                 //\n");
    printf("/////////////////////////////////////////////////////\n\n");
}

void sair(){        // sai do sistema e salva todas as informações nos aruivos binarios
    FILE *fp = fopen(bdlin, "wb");  // abre "linhas.bin" para escrita
    
    fwrite(&num_linhas, sizeof(int), 1, fp);    // grava o numero de linhas
    fwrite(&cont_Lin, sizeof(int), 1, fp);      // grava o codigo da ultima linha

    fwrite(lin, sizeof(Linha), num_linhas, fp); // grava todas as linhas
    free(lin);      // libera a memoria do vetor 'lin'
    fclose(fp);     // fecha 'linhas.bin'

    fp = fopen(bdoni, "wb");        // abre "onibus.bin" para escrita
    fwrite(&num_onibus, sizeof(int), 1, fp);    // grava a quantidade de onibus

    fwrite(oni, sizeof(Onibus), num_onibus, fp);    // grava todos os onibus
    free(oni);      // libera a memoria do vetor 'oni'
    fclose(fp);     // fechar 'onibus.bin'

    printf("Saindo...\n");
}