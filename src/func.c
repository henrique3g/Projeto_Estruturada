#include "func.h"

 void cls(){        // Função para limpar a tela
        system("clear");        // linux/mac:bash
    /* #ifdef __unix__
        system("clear");        // linux/mac:bash
    #elif defined(_WIN32) || defined(WIN32)
        system("cls");          // windows:cmd
    #endif */
} 

void clearBuf(){        // Função para limpar o buffer de entrada (stdin)
    char c;
    while((c = getchar()) != '\n' && c != EOF); // Enquanto tiver caracteres no buffer fazer leitura
}

void pause(){       // Função de pause
    clearBuf();     // Chama clearBuf para pausar o fluxo
}
void lerString(char *s, char *msg){     // Função para ler uma string
    do{     // Inicia um loop infinito enquanto não for digitados caracteres validos
        printf("%s",msg);               
        fgets(s, MAX, stdin);
        rmvLn(s);       // Remove o '\n' do fim da string lida
        trim(s);        // Remove os espaços em branco no inicio e no fim da string lida
        toUpperCase(s); // Passa todo inicio de palavra para maiuscula
        if(!strcmp(s, "")){ // Verifica se a string está vazia
            danger("Erro! Digite algo!\n");     // Se tiver da mensagem de erro e faz a leitura novamente
        }else{          // Se não estiver 
            return;     // Finaliza a função
        }
    }while(1);
}

void rmvLn(char *s){        // Função que remove o '\n' do final da string
    if(s[strlen(s) - 1] == '\n')    // se o penultimo caracter for '\n'
        s[strlen(s) - 1] = '\0';    // Substitui por '\0'
}

void toUpperCase(char *s){      // Passa todo inicio de palavra para maiuscula
    for(unsigned int i = 0; i < strlen(s); i++){
        if(!i)  *s = toupper(*s);   // Se for o primeiro caracter passa para caixa alta
        else{
            s[i] = tolower(s[i]);
            if(s[i] == ' '){       // Se o caracter atual for ' ' passa o proximo para caixa alta
                s[i+1] = toupper(s[i+1]);
                i++;
            }
        }
    }
}

int isPar(int n){       // retorna se o numero passado é par ou não
    if(n % 2)       // não é par retorna 0
        return 0;
    return 1;       // se for par retorna 1
}

void trim(char *s){     // função q remove os espaços em branco do inicio e do fim da string
    int i = 0;

    for(i = 0; s[i] == ' '; i++);   // conta quando caracteres branco existem no inicio
    strcpy(s, s+i);     // copiar a string a partir do primeiro caracter que não seja espaço
    
    for(i = strlen(s)-1; s[i] == ' ' ; i--)   s[i] = '\0';      // enquanto o ultimo caracter valido for ' ' substitui por '\0'

}

int isNum(char *s){     // retorna 1 se a string for um numero valido e zero se não for
    for(unsigned int i = 0; i < strlen(s); i++){    
        if(s[0] == '-' && i == 0){      // se o caracter for um '-' pula pro proximo caracter
            continue;    
        }
        if(!isdigit(s[i])){     // se encontrar algum caracter que não seja parte de um numero retorna 0
            return 0;
        }
    }
    return 1;   // se não achou nenhum caracter que não seja numero retorna 1
}

void lerData(Data *d){      // ler uma data valida
	printf("Data: ");
    scanf("%2d/%2d/%4d", &d->dia, &d->mes, &d->ano);
    clearBuf();
    while(!validaData(*d)){ // enquanto a data não for valida emite uma msg de erro e faz a leitura novamente
        danger("Erro! Data invalida!\n");
        printf("Data: ");
        scanf("%2d/%2d/%4d", &d->dia, &d->mes, &d->ano);
        clearBuf();
    }
    
}

void lerHora(Hora *h){      // ler uma data valida
	printf("Horário de partida: ");
	scanf("%2d:%2d", &h->h, &h->m);
	clearBuf();
	while(!validaHora(*h)){     // enquanto a hora não for valida emite uma msg de erro e faz a leitura novamente
		danger("Erro! Hora invalida!\n");
		printf("Horário de partida: ");
		scanf("%2d:%2d", &h->h, &h->m);
		clearBuf();
	}
}

Data getData(){     // retorna a data atual do sistema
    Data d;
    time_t t;
    struct tm *tp;
    time(&t);
    tp = localtime(&t);
    d.dia = tp->tm_mday;
    d.mes = tp->tm_mon+1;
    d.ano = tp->tm_year+1900;
    return d;
}

Hora getHora(){     // retorna a hora atual do sistema
    Hora h;
    time_t t;
    struct tm *tp;
    time(&t);
    tp = localtime(&t);
    h.h = tp->tm_hour;
    h.m = tp->tm_min;
    return h;
}

void dateToTm(Data d, struct tm *tm){   // passa uma 'Data' para 'Struct tm'
    tm->tm_mday = d.dia;
    tm->tm_mon = d.mes-1;
    tm->tm_year = d.ano-1900;
}

int getDiaSemana(Data d){       // retorna qual o dia da semana da data passada
    time_t t;
    struct tm tm = {0},*tmi;
    int dia;
    dateToTm(d, &tm);

    t = mktime(&tm);

    tmi = localtime(&t);
    
    dia = tmi->tm_wday;

    return dia;
   
}


int diffDate(Data final){       // retorna a diferença entre a data passada e a data atual do sistema
    int diff;
    time_t ti, tf;
    struct tm *tmi, tmf = {0};
    // inicia a data atual
    time(&ti);
    tmi = localtime(&ti);
    // inicia a data final
    tmf.tm_hour = tmi->tm_hour; 
    tmf.tm_min = tmi->tm_min+1;
    tmf.tm_mday = final.dia;
    tmf.tm_mon = final.mes-1;
    tmf.tm_year = final.ano-1900;
    // passa a data atual para segundos
    tf = mktime(&tmf);
    
    diff = tf - ti;     // calcula a diferena de segundos entre as duas datas
    diff = diff/3600/24;    // passa os segundos para dias
    
    return diff; //retorna a diferena de dias
}


int validaData(Data d){     // retorna se a data é valida ou não (1 valida , 0 invalida)
    if((d.dia >= 1 && d.dia <= 31) && (d.mes >= 1 && d.mes <= 12) && (d.ano > 2000 && d.ano <= 2100)){
        int dias_mes[2][12] = {{31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
                               {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}};

        if(d.dia <= dias_mes[d.ano%4==0?1:0][d.mes-1])
            return 1;
       
    }
    return 0;
}

int validaHora(Hora h){     // retorna se a hora é valida (1 valida, 0 invalida)
    if((h.h >= 0 && h.h <= 23) && (h.m >= 0 && h.m <= 59))
        return 1;
    return 0;
}


// mensage coloridas
void danger(char *texto){   // printf vermelho
    printf("\033[31m%s\033[m",texto);
}

void success(char *texto){  //printf verde
    printf("\033[32m%s\033[m",texto);
}

void warning(char *texto){  // printf amarelo
    printf("\033[33m%s\033[m",texto);
}