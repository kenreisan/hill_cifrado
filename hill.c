#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MODULE 27
#define LETRAS 26

int alfabeto[] = {'A','B','C','D','E','F','G','H','I','J','K','L','M',
				'N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};

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

int * formato_frase(char *str_original, int n){
	/*Quita espacios y caracteres especiales*/
	int pos = 0;
	int pos2 = 0;
	int largo = strlen(str_original);

	//char *nueva = malloc((largo + sumarpos) * sizeof (char));
	int *nueva = malloc( largo * sizeof (int));

	while ( str_original[pos] != '\0'){
		if (!isspace (str_original[pos]) ){
			if (str_original[pos] == -61)	/*el caracter "Ñ" se divide en 2 partes*/
				nueva[pos2++] = 'N';		/*-61 y -111, si lo detecta lo pasa a 'N'*/
			else if ((str_original[pos] >= 65) && (str_original[pos] <= 90))
				nueva[pos2++] = str_original[pos];	/*solo acepta mayusculas [A-Z]*/
		}
		pos++;
	}

	int modulo = pos2 % n;
	int relleno = n - modulo;

	if (modulo != 0){
		for (int i = 0; i < relleno; ++i)
		{
			nueva[pos2++] = 'X';
		}
	}

	return nueva;
}

int * validar_alfabeto(int *frase){

	int pos = 0;

	while(frase[pos] != '\0'){
		for (int j = 0; j < LETRAS; j++){
			if (frase[pos] == alfabeto[j]){
				frase[pos] = j;
			}
		}
		pos++;
	}
	return frase;
}

void separar_frase(int *frase, int dimension, int tamanio){

	int pos = 0;

	while(pos != tamanio){
		for (int j = 0; j < dimension; ++j)
		{
			printf("%c",frase[pos++]);
		}
		if (pos != tamanio)
			printf(",");
	}
	printf("\n");
}

int main(int argc, char *argv[])
{
	if (argc != 5){
		printf("\n[Requiere Indicar]$ nFilas nColumnas m,a,t,r,i,z %cfrase%c\n", '"', '"');
		printf("Programa terminado.\n\n");
		return 1;
	}

	int i = 0;
	int x = 0;
	int **A;
	char *frase = argv[4];
	int fil = atoi(argv[1]);
	int col = atoi(argv[2]);
	int *frase_sin_espacios;
	
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

	frase_sin_espacios = formato_frase(frase, fil);

	while (frase_sin_espacios[i] != '\0'){
		printf("%c", frase_sin_espacios[i]);
		i++;
	}
	printf("\n");

	separar_frase(frase_sin_espacios, fil, i);

	validar_alfabeto(frase_sin_espacios);

	while (x < i){
		printf("( ");
		for (int i = 0; i < fil; ++i)
		{
			printf("%d ", frase_sin_espacios[x++]);
		}
		printf(") ");
	}
	printf("\n");

	return 0;
}