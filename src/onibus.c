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

void iniciarAssentos(Onibus *o){
	int count = 0;
	int lin = o->idLin;
	Data d = o->data;
	
	if(!pesquisaDataOnibus(o)){
		o->id = getCodOni();
		o->data = d;
		o->idLin = lin;
		for(int i = 0; i < 20; i++){
			if(count == 2){
				o->ass[i] = i+2;
				o->ass[i+1] = i+1;
				i++;
				count = 0;
				continue;
			}
			o->ass[i] = i+1;
			count++;
		}	
	}
}

int verificaAssento(Onibus o, int a){
	for(int i = 0; i < 20; i++){
		if(o.ass[i] == a)
			return 1;
	}
	return 0;
}