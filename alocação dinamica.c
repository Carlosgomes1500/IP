#include "stdio.h"
#include "stdlib.h"

int main()
{
	int *codigo = NULL;
	int i=0;

	codigo=(int*)malloc(sizeof(int));
	scanf("%d",codigo[i]);
	printf("%d\n",*codigo[i]);
	for(i=0;codigo[i]!=10;i++)
	{
		printf("%d\n",codigo[i]);
		codigo=(int*)realloc(codigo,(i+1)*sizeof(int));
		scanf("%d",codigo[i]);
	}

	free(codigo);
	return 0;
}