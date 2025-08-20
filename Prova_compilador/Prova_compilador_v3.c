// o problema esta no scanf da alocação dinamica
#include "stdio.h"
#include "stdlib.h"

int leia(int **codigo);

int main ()
{
	int *codigo = NULL;
	int i;
	int n_elementos = leia(&codigo);
	for(i=0;i < n_elementos;i++)
	{
		printf("%d \n",codigo[i]);
	}
	free(codigo);
	return 0;
}

int leia(int **codigo)
{
	int n_elementos = 0;
	*codigo = (int *) malloc(sizeof(int));
	do
	{
		scanf("%d",codigo[n_elementos]);
		n_elementos++;
		*codigo = (int*)realloc(*codigo,(n_elementos+1)*sizeof(int));
		
	}while(*codigo[n_elementos-1] != 10);
	return n_elementos;
}
