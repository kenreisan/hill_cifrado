#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MODULE 27
#define LETRAS 26

int alfabeto[] = {'A','B','C','D','E','F','G','H','I','J','K','L','M',
				'N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};

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

int * sin_espacios(char *str_original){
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
	return nueva;
}

int * validar_alfabeto(int *frase){

	int pos = 0;
	int existe = 0;

	while(frase[pos] != '\0')
	{
		existe = 1;
		for (int j = 0; j < LETRAS; j++)
		{
			if (frase[pos] == alfabeto[j])
			{
				printf("%c,",frase[pos]);
				frase[pos] = j;
				printf("%d\n",frase[pos]);
				existe = 0;
			}
		}
		pos++;
	}
	return frase;
}

void separar_frase(char *frase, int tamanio){

	while (*frase != '\0'){
		
		switch (*frase){

			case 'A':
				printf("0,");
				break;
			
			case 'B':
				printf("1,");
				break;
			
			case 'C':
				printf("2,");
				break;

			case 'D':
				printf("3,");
				break;

			case 'E':
				printf("4,");
				break;

			case 'F':
				printf("5,");
				break;

			case 'G':
				printf("6,");
				break;

			case 'H':
				printf("7,");
				break;

			case 'I':
				printf("8,");
				break;

			case 'J':
				printf("9,");
				break;

			case 'K':
				printf("10,");
				break;

			case 'L':
				printf("11,");
				break;

			case 'M':
				printf("12,");
				break;

			case 'N':
				printf("13,");
				break;

			case 'O':
				printf("14,");
				break;

			case 'P':
				printf("15,");
				break;

			case 'Q':
				printf("16,");
				break;

			case 'R':
				printf("17,");
				break;

			case 'S':
				printf("18,");
				break;

			case 'T':
				printf("19,");
				break;

			case 'U':
				printf("20,");
				break;

			case 'V':
				printf("21,");
				break;

			case 'W':
				printf("22,");
				break;

			case 'X':
				printf("23,");
				break;

			case 'Y':
				printf("24,");
				break;

			case 'Z':
				printf("25,");
				break;
		}
		frase++;
	}
}

int main(int argc, char *argv[])
{
	if (argc != 5){
		printf("\n[Requiere Indicar]$ nFilas nColumnas m,a,t,r,i,z %cfrase%c\n", '"', '"');
		printf("Programa terminado.\n\n");
		return 1;
	}

	int i = 0;
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

	frase_sin_espacios = sin_espacios(frase);

	while (frase_sin_espacios[i] != '\0'){
		printf("%c", frase_sin_espacios[i]);
		i++;
	}
	printf("\n");
	i = 0;

	frase_sin_espacios = validar_alfabeto(frase_sin_espacios);

	while (i < 27){
		printf("%d,", frase_sin_espacios[i]);
		i++;
	}
	printf("\n");


	return 0;
}