#include "func.h"

 void cls(){
    #ifdef __unix__
        system("clear");
    #elif defined(_WIN32) || defined(WIN32)
        system("cls");
    #endif
} 

void clearBuf(){
    char c;
    while((c = getchar()) != '\n' && c != EOF);

}

void lerString(char *s){
    fgets(s, MAX, stdin);
    rmvLn(s);
    toUpperCase(s);
}

void rmvLn(char *s){
    if(s[strlen(s) - 1] == '\n')
        s[strlen(s) - 1] = '\0';
}

void toUpperCase(char *s){
    for(unsigned int i = 0; i < strlen(s); i++){
        if(!i)  toUpper(s);
        else{
            toLower(&s[i]);
            if(s[i] == ' '){
                toUpper(&s[i+1]);
                i++;
            }
        }
    }
}

void toUpper(char *c){
    if(*c > 96 && *c < 123)
        *c -= 32;
}

int isPar(int n){
    if(n % 2)
        return 0;
    return 1;
}

void toLower(char *c){
    if(*c > 64 && *c < 91)
        *c += 32;
}

int isNum(char *s){
    for(unsigned int i = 0; i < strlen(s); i++)
        if(!isCharNum(s[i]))
            return 0;
    return 1;
}

int isCharNum(char c){
    if(c > 47 && c < 57)
        return 1;
    return 0;
}

int isChar(char c){
    toUpper(&c);
    if(c > 64 && c < 91)
        return 1;
    return 0;
}

void lerData(Data *d){
	scanf("%2d/%2d/%4d", &d->dia, &d->mes, &d->ano);
    clearBuf();
}

Data getData(){
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

Hora getHora(){
    Hora h;
    time_t t;
    struct tm *tp;
    time(&t);
    tp = localtime(&t);
    h.h = tp->tm_hour;
    h.m = tp->tm_min;
    return h;
}

void dateToTm(Data d, struct tm *tm){
    tm->tm_mday = d.dia;
    tm->tm_mon = d.mes-1;
    tm->tm_year = d.ano-1900;
}

int getDiaSemana(Data d){
    time_t t;
    struct tm tm = {0},*tmi;
    int dia;
    dateToTm(d, &tm);

    t = mktime(&tm);

    tmi = localtime(&t);
    
    dia = tmi->tm_wday;

    return dia;
   
}


int diffDate(Data final){
    int diff;
    time_t ti, tf;
    struct tm *tmi, tmf = {0};
    
    time(&ti);
    // tmi = localtime(&ti);
    // tmf.tm_hour = tmi->tm_hour+1;
    // tmf.tm_min = tmi->tm_min;
    tmf.tm_mday = final.dia;
    tmf.tm_mon = final.mes-1;
    tmf.tm_year = final.ano-1900;
    
    tf = mktime(&tmf);
    
    diff = tf - ti;
    diff = diff/3600/24;
    
    return diff+1;
}


int validaData(Data d){
    if((d.dia >= 1 && d.dia <= 31) && (d.mes >= 1 && d.mes <= 12) && (d.ano > 2000 && d.ano <= 2100)){
        int dias_mes[2][12] = {{31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
                               {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}};

        if(d.dia <= dias_mes[d.ano%4==0?1:0][d.mes-1])
            return 1;
       
    }
    return 0;
}

int validaHora(Hora h){
    if((h.h >= 0 && h.h <= 23) && (h.m >= 0 && h.m <= 59))
        return 1;
    return 0;
}