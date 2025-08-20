//===Declaração de bibliotecas=========
#include <stdio.h>
#include <stdlib.h>

//===Delraração de estuturas===========
typedef struct tipoElemento{ //Tipo da estrutura que amazenara a ascoodenadas e o valor do elemento da matriz
	int x; //coodenada x do valor da matriz
	int y; //coodenada y do valor da matriz
	float valor;//valor que tera 
}tipoElemento;
//==========Fim  da declaração de estuturas====
//==========Prototico das funções auxiliares===
int *ler()
{
	int *p, x;
		printf("oi1\n");

	scanf("%d", &x);
			p = &x;

		printf("oi2\n");

	//printf("p=%d\n",p);
	return p;
}
//========Fim Prototico das funções auxiliare==
//==========Função Principal do progama======
int main()
{
	int *pointer;
	tipoElemento e;
	pointer=ler();
	printf("*p=%d\n",*pointer);
	//scanf("%d %d %f",&elemento.x,&elemento.y,&elemento.valor);
	//printf("%d %d %f",elemento.x,elemento.y,elemento.valor);
	return 0;
}
//==========Fim da função main================