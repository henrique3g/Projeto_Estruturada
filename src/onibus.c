#include "onibus.h"

int mostrarAssentos(Onibus o){
	int count = 1;
	int dis = 0;
	for(int i = 0; i < 20; i++){
		if(o.ass[i] != -1){
			printf("%02d", o.ass[i]);
			dis = 1;
		}else{
			printf(" X");
		}
		printf("%c",count == 2?'\t':count == 4?'\n':' ');
		
		if(count == 4)	count = 0;
		count++;
	}
	return dis;
}

Onibus* carregarOnibus(){
	FILE *fp = fopen(bdoni, "rb");
	if(!fp){
        fp = fopen(bdoni, "wb");
		cont_oni = 0;
        num_onibus = 0;
    }else{
        if(fread(&num_onibus, sizeof(int), 1, fp)){
			if(fread(&cont_oni, sizeof(int), 1, fp)){
				if(num_onibus){
					oni = malloc(sizeof(Onibus)*num_onibus);
					if(fread(oni, sizeof(Onibus), num_onibus, fp)){
						fclose(fp);
						return oni;
					}

				}
			}
        }
    }
    fclose(fp);
    return NULL;
}

int pesquisarOnibus(int l, Data *d){
	
	
	if(l != -1){
		cls();
		cabecalho(6);
		mostrarLinha(lin[l]);
		printf("Data: ");
		lerData(d);
		while(!validaData(*d)){
			printf("Erro! Data invalida!\n");
			printf("Data: ");
			lerData(d);
		}
		
	}

	for(int i = 0; i < num_onibus; i++){
		if(oni[i].idLin == l){
			if(oni[i].data.dia == d->dia && oni[i].data.mes == d->mes && oni[i].data.ano == d->ano){
				return i;
			}
		}
		
	}
	return -1;
}


void consultarAssentos(){
	int l = pesquisarLinha();
	if(l == -1){
		printf("Erro! Não há linhas cadastradas!\n");
		getchar();
		return;
	}
	Data d;
	int o = pesquisarOnibus(l, &d);
	int ass;
	if(o == -1){
		iniciarAssentos();
		o = num_onibus-1;
		oni->id = cont_oni;
		oni->idLin = l;
		oni->data = d;
	}
	do{
		cls();
		cabecalho(6);
		mostrarLinha(lin[l]);
		printf("Data: %02d/%02d/%04d\n", d.dia, d.mes, d.ano);
		if(mostrarAssentos(oni[o])){

			printf("assento para reservar (0 para cancelar): ");
			scanf("%2d", &ass);
			clearBuf();
			if(ass >= 1 && ass <= 20){		//Verifica se o numero digitado esta entre os 20 possiveis
				for(int i = 0; i < 20; i++){		//For para achar o assento a ser reservado
					if(oni[o].ass[i] == ass)
						oni[o].ass[i] = -1;			//Reserva o assento
				}
			}
		}else{
			printf("Todos os assentos estão ocupados!\n");
			getchar();
			break;
		}
	}while(ass != 0);
}

void iniciarAssentos(){
	num_onibus++;
	cont_oni++;
	oni = realloc(oni, sizeof(Onibus)*num_onibus);
	int count = 0;
	for(int i = 0; i < 20; i++){
		if(count == 2){
			oni[num_onibus-1].ass[i] = i+2;
			oni[num_onibus-1].ass[i+1] = i+1;
			i++;
			count = 0;
			continue;
		}
		oni[num_onibus-1].ass[i] = i+1;
		count++;
	}	
}