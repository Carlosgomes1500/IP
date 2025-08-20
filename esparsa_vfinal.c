#include <stdio.h>
#include <stdlib.h>

typedef struct ElementoEsparsa
{
	int x;
	int y;
	float valor;
}ElementoEsparsa;

void criacao(ElementoEsparsa **Elemeno,int *tamanho);
void imprime(ElementoEsparsa **Elemeno,int *tamanho);
void grava(ElementoEsparsa **Elemeno,int *tamanho);
void ler(ElementoEsparsa **Elemeno,int *tamanho);

int main()
{
	ElementoEsparsa *Elemeno=NULL;
	int tamanho;
	
	criacao(&Elemeno,&tamanho);
	
	imprime(&Elemeno,&tamanho);
		
	grava(&Elemeno,&tamanho);

	free(Elemeno);

	ElementoEsparsa *Elemeno2=NULL;

	ler(&Elemeno2,&tamanho);

	imprime(&Elemeno2,&tamanho);

	free(Elemeno2);
	return 0;
}
void imprime(ElementoEsparsa **Elemeno,int *tamanho)
{
	int tam,i,j;

	for(tam=0,i=0;i<(*tamanho);i++)
	{
		if(Elemeno[0][i].x>tam)
		{
			tam=Elemeno[0][i].x;
		}
		if(Elemeno[0][i].y>tam)
		{
			tam=Elemeno[0][i].y;
		}
	}

	//printf("tam=%d\n",tam);
	tam++;

	float **matriz;

	matriz=(float**)malloc(sizeof(float*)*tam);
	for(i=0;i<tam;i++)
	{
		matriz[i]=(float*)calloc(tam,sizeof(float));
	}
	for(i=0;i<(*tamanho);i++)
	{
		matriz[Elemeno[0][i].x][Elemeno[0][i].y]=Elemeno[0][i].valor;
	}
	for(i=0;i<tam;i++)
	{
		for(j=0;j<tam;j++)
		{
			printf("%.0f ",matriz[i][j]);
		}
		printf("\n");
	}
	//printf("\n\n\n");
	free(matriz);

}
void criacao(ElementoEsparsa **Elemeno,int *tamanho)
{
	//printf("Quantos Elemenos tera a matriz espaça\n");
	scanf("%d",tamanho);
	Elemeno[0]=(ElementoEsparsa*)malloc((sizeof(ElementoEsparsa))*(*tamanho));
	int i;
	for (i = 0; i < (*tamanho); ++i)
	{
		scanf("%d",&(Elemeno[0][i].x));
		//printf("%d\n",(Elemeno[0][i].x));
		scanf("%d",&(Elemeno[0][i].y));
		//printf("%d\n",(Elemeno[0][i].y));
		scanf("%f",&(Elemeno[0][i].valor));
		//printf("%.2f\n",(Elemeno[0][i].valor));
	}
}
void grava(ElementoEsparsa **Elemeno,int *tamanho)
{

	FILE *arq;
	arq=fopen("matriz.bin","wb");
	fwrite(Elemeno[0],sizeof(ElementoEsparsa),*tamanho,arq);
	printf("gravado\n");



	fclose(arq);
}
void ler(ElementoEsparsa **Elemeno,int *tamanho)
{
	FILE *arq;
	arq = fopen("matriz.bin","rb");

	Elemeno[0]=(ElementoEsparsa*)malloc(sizeof(ElementoEsparsa)*(*tamanho));

	fread(&Elemeno[0][0],sizeof(ElementoEsparsa),*tamanho,arq);

	printf("lido\n");

	fclose(arq);
}