#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MODULE 27

int mod(int a){
	int r;
	r = a % MODULE;

	return r;
}

int **leer_matriz(int ** matriz_a, int filas, int columnas, char *cadena){

	matriz_a = (int **)malloc(filas * sizeof(int*));

	for (int i ; i < filas; i++){
		matriz_a[i] = (int *)malloc(columnas * sizeof (int));
	}

	char *token = strtok(cadena, ",");

	if(token != NULL){
		for (int i = 0; i < filas; ++i)
		{
			for (int j = 0; j < columnas; ++j)
			{
				matriz_a[i][j] = atoi(token);
				//printf("[%d, %d] = %d\n",i, j, matriz_a[i][j]);
				token = strtok(NULL, ",");
			}
		}
	}
	return matriz_a;
}

void separar_frase(char *frase){

}



int main(int argc, char *argv[])
{
	if (argc != 5){
		printf("\n[Requiere Indicar]$ nFilas nColumnas m,a,t,r,i,z %cfrase%c\n", '"', '"');
		printf("Programa terminado.\n\n");
		return 1;
	}

	int **A;
	int fil = atoi(argv[1]);
	int col = atoi(argv[2]);
	char *frase = argv[4];
	
	A = leer_matriz(A ,atoi(argv[1]), atoi(argv[2]), argv[3]);
	printf("%s\n",frase);

	/*imprime bonita la matriz dada*/
	for (int i = 0; i < fil; ++i){
		printf("[");
		for (int j = 0; j < col; ++j){
			if (j == 0)
				printf("%2d", A[i][j]);
			else
				printf(",%2d", A[i][j]);
		}
		printf("]\n");
	}



	return 0;
}