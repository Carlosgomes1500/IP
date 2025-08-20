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
	int *arr = (int *) malloc(sizeof(int));
	do
	{
		scanf("%d", &arr[n_elementos]);
		n_elementos++;
		arr = (int*)realloc(arr,(n_elementos+1)*sizeof(int));
		
	}while(arr[n_elementos-1] != 10);
	*codigo = arr;
	return n_elementos;
}