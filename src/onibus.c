#include "onibus.h"

int mostrarAssentos(int o){	// mostra os assentos do onibus
	int count = 1;
	int dis = 0;
	for(int i = 0; i < 20; i++){	// verifica se o assento esta ou não reservado
		if(oni[o].ass[i] != -1){	// se não esta mostra o numero do assento
			printf("%02d", oni[o].ass[i]);
			dis = 1;
		}else{	// se esta mostra um x vermelho
			danger(" X");
		}
		printf("%c",count == 2?'\t':count == 4?'\n':' ');	// a cada 2 assentos dar '\t' e a cada 4 '\n'
		
		if(count == 4)	count = 0;
		count++;
	}
	return dis; // retorna se tem assentos disponiceis ou não
}

void carregarOnibus(){		// carrega a quantidade de onibus e todos os onibus
	FILE *fp = fopen(bdoni, "rb");
	int err = 0;
	if(!fp){	// se não existir arquivo 'onibus.bin' inicar do zero
        num_onibus = 0;
    }else{
		if(fread(&num_onibus, sizeof(int), 1, fp)){	// verifica se conseguiu ler o numero de onibus
			if(num_onibus){	//verifica se tem alguma onibus se tiver faz a leitura
				oni = malloc(sizeof(Onibus)*num_onibus);	// aloca memoria
				if(fread(oni, sizeof(Onibus), num_onibus, fp)){	// ler todos os onibus
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
		if(err){	// se char aq e err for 1 sai do sistema
			danger("Erro ao ler arquivo");
			pause();
			exit(1);
		}
    }
}

int pesquisarOnibus(int l, Data *d){	// pesquisa um onibus pela linha e data
	for(int i = 0; i < num_onibus; i++){
		if(lin[l].id == oni[i].idLin){
			if(oni[i].data.dia == d->dia && oni[i].data.mes == d->mes && oni[i].data.ano == d->ano){
				return i;
			}
		}
	}
	return -1;	// se não econtrar nenhum retorn -1
}


void consultarAssentos(){	// consultar assentos
	int l = pesquisarLinha();	// pesquisa linha
	int diff,flag;
	if(l == -1){	// verifica se linha existe
		danger("Erro! Não há linhas cadastradas!\n");
		pause();
		return;
	}
	if(!lin[l].ativo){	// verifica se linha esta ativa
		danger("Linha inativa!");
		pause();
		return;
	}

	// limpa tela e mostra linha
	cls();
	cabecalho(6);
	mostrarLinha(lin[l]);
	// ler data
	Data d;
	lerData(&d);


	if(diffDate(d) > 30){	// verifica se a data informada é inferior a 30 dias
		warning("Data de consulta superior a 30 dias!\n");
		pause();
		return;
	}
	int o = pesquisarOnibus(l, &d);	// pesquisa onibus
	int ass;
	if(o == -1){	// se o onibus não tiver sido iniciado inicia
		// inicia onibus
		iniciarAssentos();
		o = num_onibus-1;
		oni[o].idLin = lin[l].id;
		oni[o].data = d;
	}
	do{
		// imprime linha e data
		cls();
		cabecalho(6);
		mostrarLinha(lin[l]);
		printf("Data: %02d/%02d/%04d\n", d.dia, d.mes, d.ano);

		flag = mostrarAssentos(o);	// mostra os assentos e retorna se tem assentos disponiveis
		diff = diffDate(oni[o].data);	// verifica a diferença de datas

		// verifica se o onibus ja partiu
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
			// se tem assentos disponiveis pergunta se quer reservar algum
			printf("assento para reservar (");
			danger("0 para Sair");
			printf("): ");
			scanf("%d", &ass);
			clearBuf();
			if(!ass) return;	// se for 0 sai da função
			if(ass >= 1 && ass <= 20){		//Verifica se o numero digitado esta entre os 20 possiveis
				for(int i = 0; i < 20; i++){		//For para achar o assento a ser reservado
					if(oni[o].ass[i] == ass){
						oni[o].ass[i] = -1;			//Reserva o assento
						flag = 0;
						success("Reserva realizada!");
						pause();
					}
				}
				if(flag){	// se assento estiver ocupado
					warning("Assento ocupado!");
					pause();
				}
				continue;
			}
		}else if(flag == -1){	// se onibus ja tiver partido
			warning("Onibús já partiu!\n");
			pause();
			break;
		}
		if(flag == 0){	// se todos os assentos estão ocupados
			char s[5];
			warning("Todos os assentos estão ocupados!\n");
			fgets(s, sizeof(s), stdin);
			rmvLn(s);
			trim(s);
			ass = atoi(s);
		}
		// verifica se é para cancelar alguma reserva
		if(ass <= -1 && ass >= -20){
			ass *= -1;
			//ass;
			int count = 0;
			for(int i = 0; i < 20; i++){		//For para achar o assento a ser reservado
				if(count == 2){
					if(ass == i+2)
						oni[o].ass[i] = i+2;
					if(ass == i+1)
						oni[o].ass[i+1] = i+1;
					i++;
					count = 0;
					continue;
				}
				if(ass == i+1) 
					oni[o].ass[i] = i+1;
				count++;
				
			}
			continue;
		}
		return;
		
	}while(ass != 0);
}

void iniciarAssentos(){		// inicia os assentos do onibus
	num_onibus++;
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

int getTotReserva(Onibus o){	// conta o total de reserva no onibus
	int soma = 0;
	for(int i = 0; i < 20; i++){
		if(o.ass[i] == -1)
			soma++;
	}
	return soma;
}

void lerReserva(){		// ler reserva de arquivo texto
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

	// ler nome do arquivo
	printf("Arquivo: ");
	fgets(arq, sizeof(arq), stdin);
	rmvLn(arq);
	// pega o nome do arquivo
	// sprintf(log, "relatorios/log \"%s\" %02d-%02d-%04d %02d:%02d.txt",arq, tm->tm_mday,tm->tm_mon+1, tm->tm_year+1900, tm->tm_hour, tm->tm_min);
	sprintf(log, "relatorios/log \"%s\" %02d-%02d-%04d %02d:%02d:%02d.txt",arq, tm->tm_mday,tm->tm_mon+1, tm->tm_year+1900, tm->tm_hour, tm->tm_min, tm->tm_sec);

	// abre arquivo de reserva
	FILE *fo = fopen(arq, "r");
	if(fo == NULL){		// verifica se conseguiu abrir arquivo de reserva
		danger("Erro ao abrir o arquivo de reservas!\n");
		pause();
		return;
	}	
	// abre arquivo de logs
	flog = fopen(log, "w");
	if(flog == NULL){
		danger("Erro ao criar o arquivo de LOG!\n");
		pause();
		return;
	}
	// imprime titulo na tela e no log
	printf("\n-----------------------------------------------------\nRelatório de LOG\n-----------------------------------------------------\n");
	fprintf(flog, "-----------------------------------------------------\nRelatório de LOG\n-----------------------------------------------------\n");
	// faz a leitura das reservas
	while(!feof(fo)){
		count = 0;
		// faz a leitura do nome da cidade
		do{
			c = getc(fo);	// ler caracter por caracter
			// verifica se é um caracter valido
			if((isalnum(c) || c == '-') || (c == ' ' && count != 0)){
				cid[count] = c;
				count++;
			}
		}while (c != ',' && c != EOF);
		cid[count] = '\0';
		toUpperCase(cid);
		// faz a leitura dos dados da reserva e verifica se consegui ler	
		if(fscanf(fo, " %02d:%02d, %02d/%02d/%4d, %02d", &h.h,&h.m, &d.dia,&d.mes, &d.ano, &ass) == 6){
			sprintf(str, "%s, %02d:%02d, %02d/%02d/%04d, %02d", cid, h.h, h.m, d.dia, d.mes, d.ano, ass);
			
			// faz algumas verificações sobre esses dados da reserva
			
			// valida hora
			if(!validaHora(h)){
				logErro(str, "Horário inválido!");
				continue;
			}
			// valida data
			if(!validaData(d)){
				logErro(str, "Data invalida!");
				continue;
			}
			// verifica se a data é superir a 30 dias
			if(diffDate(d) > 30){
				logErro(str, "Data superior a 30 dias!");
				continue;
			}
			// verifica se é um assento valido
			if(!(ass >= 1 && ass <= 20)){
				logErro(str, "Assento inválido!");
				continue;
			}
			
			l = pesquisarLinNome(cid, h); // pesquisa cidade
			if(l == -1){
				logErro(str, "Linha não existe!");
				continue;
			}
			// verifica se esta ativa
			if(!lin[l].ativo){
				logErro(arq, "Linha inativa!");
				continue;
			}
			o = pesquisarOnibus(l, &d);	// pesquisa onibus
			if(o == -1){	// verifica se existe
				iniciarAssentos();	// se não existir inicia
				o = num_onibus-1;
				oni[o].idLin = lin[l].id;
				oni[o].data = d;
			}
			//verifica se o onibus ja partiu
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
			// tenta fazer a reserva
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
			// verifica o resultado da reserva
			if(res == 1){
				logErro(str, "Reserva realizada!");
			}else if(res == -1){
				logErro(str, "ônibus cheio!");
			}else if(res == 0){
				logErro(str, "Assento ocupado!");
			}		
		}
	}
	// fechar os arquivos quando terminar o arquivo de reservas
	fclose(flog);
	fclose(fo);
	printf("-----------------------------------------------------\n\n");
	printf("Arquivo processado com sucesso!\nRelatório gravado em log.txt.");
	pause();
}