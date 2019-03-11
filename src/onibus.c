#include "onibus.h"

int mostrarAssentos(int o){
	int count = 1;
	int dis = 0;
	for(int i = 0; i < 20; i++){
		if(oni[o].ass[i] != -1){
			printf("%02d", oni[o].ass[i]);
			dis = 1;
		}else{
			danger(" X");
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
		lerData(d);
		
	}

	for(int i = 0; i < num_onibus; i++){
		if(oni[i].idLin == lin[l].id){
			if(oni[i].data.dia == d->dia && oni[i].data.mes == d->mes && oni[i].data.ano == d->ano){
				return i;
			}
		}
		
	}
	return -1;
}


void consultarAssentos(){
	int l = pesquisarLinha();
	int diff,flag;
	if(l == -1){
		danger("Erro! Não há linhas cadastradas!\n");
		getchar();
		return;
	}
	Data d;
	int o = pesquisarOnibus(l, &d);
	if(diffDate(d) > 30){
		warning("Data de consulta superior a 30 dias!\n");
		getchar();
		return;
	}
	int ass;
	if(o == -1){
		iniciarAssentos();
		o = num_onibus-1;
		oni[o].id = cont_oni;
		oni[o].idLin = lin[l].id;
		oni[o].data = d;
	}
	do{
		cls();
		cabecalho(6);
		mostrarLinha(lin[l]);
		printf("Data: %02d/%02d/%04d\n", d.dia, d.mes, d.ano);
		flag = mostrarAssentos(o);
		diff = diffDate(oni[o].data);
		if(diff <= 0){
			if(diff < 0){
				flag = -1;
			}else{
				if(lin[l].hora.h < getHora().h)
					flag = -1;
				else if(lin[l].hora.h == getHora().h){
					if(lin[l].hora.m < getHora().m)
						flag = -1;
				}
			}
		}
		if(flag == 1){

			printf("assento para reservar (");
			danger("0 para Sair");
			printf("): ");
			scanf("%2d", &ass);
			clearBuf();
			if(ass >= 1 && ass <= 20){		//Verifica se o numero digitado esta entre os 20 possiveis
				for(int i = 0; i < 20; i++){		//For para achar o assento a ser reservado
					if(oni[o].ass[i] == ass){
						oni[o].ass[i] = -1;			//Reserva o assento
						flag = 0;
						success("Reserva realizada!");
						getchar();
					}
				}
				if(flag){
					warning("Assento ocupado!");
					getchar();
				}
			}
		}else if(flag == 0){
			warning("Todos os assentos estão ocupados!\n");
			getchar();
			break;
		}else if(flag == -1){
			warning("Onibús já partiu!\n");
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

int getTotReserva(Onibus o){
	int soma = 0;
	for(int i = 0; i < 20; i++){
		if(o.ass[i] == -1)
			soma++;
	}
	return soma;
}

void lerReserva(){
	char arq[100], str[60], cid[MAX];
	char log[100];
	time_t t;
	time(&t);
	struct tm *tm = localtime(&t);
	Data d;
	Hora h;
	char c;
	int ass, count = -1;
	int l,o;


	printf("Arquivo: ");
	fgets(arq, sizeof(arq), stdin);
	rmvLn(arq);
	sprintf(log, "relatorios/log \"%s\" %02d-%02d-%04d %02d:%02d.txt",arq, tm->tm_mday,tm->tm_mon+1, tm->tm_year+1900, tm->tm_hour, tm->tm_min);
	// sprintf(log, "relatorios/log \"%s\" %02d-%02d-%04d %02d:%02d:%02d.txt",arq, tm->tm_mday,tm->tm_mon+1, tm->tm_year+1900, tm->tm_hour, tm->tm_min, tm->tm_sec);

	FILE *fo = fopen(arq, "r");
	if(fo == NULL){
		danger("Erro ao abrir o arquivo de reservas!\n");
		getchar();
		return;
	}	
	flog = fopen(log, "w");
	if(flog == NULL){
		danger("Erro ao criar o arquivo de LOG!\n");
		getchar();
		return;
	}
	printf("\n-----------------------------------------------------\nRelatório de LOG\n-----------------------------------------------------\n");
	fprintf(flog, "-----------------------------------------------------\nRelatório de LOG\n-----------------------------------------------------\n");
	while(!feof(fo)){
		count = 0;
		do{
			c = getc(fo);
			if((isalnum(c) || c == '-') || (c == ' ' && count != 0)){
				cid[count] = c;
				count++;
			}
		}while (c != ',' && c != EOF);
		cid[count] = '\0';
		toUpperCase(cid);

		
			
		if(fscanf(fo, " %02d:%02d, %02d/%02d/%4d, %02d", &h.h,&h.m, &d.dia,&d.mes, &d.ano, &ass) == 6){
			sprintf(str, "%s, %02d:%02d, %02d/%02d/%04d, %02d", cid, h.h, h.m, d.dia, d.mes, d.ano, ass);
			if(!validaHora(h)){
				logErro(str, "Horario invalido!");
				continue;
			}
			if(!validaData(d)){
				logErro(str, "Data invalida!");
				continue;
			}
			if(diffDate(d) > 30){
				logErro(str, "Data superior a 30 dias!");
				continue;
			}
			if(!(ass >= 1 && ass <= 20)){
				logErro(str, "Assento invalido!");
				continue;
			}
			l = pesquisaLin(cid, h);
			if(l == -1){
				logErro(str, "Linha não existe!");
				continue;
			}
			o = pesquisaOni(l, &d);
			if(o == -1){
				iniciarAssentos();
				o = num_onibus-1;
				oni[o].id = cont_oni;
				oni[o].idLin = lin[l].id;
				oni[o].data = d;
			}
			int diff = diffDate(d);
			if(diff <= 0){
				if(diff < 0){
					logErro(str, "Ônibus já partiu!");
					continue;
				}else{
					if(h.h < getHora().h){
						logErro(str, "Ônibus já partiu!");
						continue;
					}else if(h.h == getHora().h){
						if(h.m < getHora().m){
							logErro(str, "Ônibus já partiu!");
							continue;
						}
					}
				}
			}
			int res = -1;
			for(int i = 0; i < 20; i++){
				if(oni[o].ass[i] == ass){
					oni[o].ass[i] = -1;
					res = 1;
					break;
				}
				if(oni[o].ass[i] != -1){
					res = 0;
				}
			}
			if(res == 1){
				logErro(str, "Reserva realizada!");
			}else if(res == -1){
				logErro(str, "ônibus cheio!");
			}else if(res == 0){
				logErro(str, "Assento ocupado!");
			}		
		}
	}
	fclose(flog);
	fclose(fo);
	printf("-----------------------------------------------------\n\n");
	printf("Arquivo processado com sucesso!\nRelatório gravado em log.txt.");
	getchar();
}

int pesquisaOni(int l, Data *d){
	for(int i = 0; i < num_onibus; i++){
		if(lin[l].id == oni[i].idLin){
			if(oni[i].data.dia == d->dia && oni[i].data.mes == d->mes && oni[i].data.ano == d->ano){
				return i;
			}
		}
	}
	return -1;
}
