#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MODULE 27
#define LETRAS 26

int alfabeto[] = {'A','B','C','D','E','F','G','H','I','J','K','L','M',
				'N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};

int * mult_matriz(int **m_a, int *m_b, int dimension){

	int *m_c = (int *)calloc(dimension, sizeof(int));

	for (int i = 0; i < dimension; i++)
	{
		for (int j = 0; j < dimension; j++)
		{
			m_c[i] = m_c[i] + ( m_a[i][j] * m_b[j] );
		}
	}

	for (int n = 0; n < dimension; n++)
	{
		printf("%d\n", m_c[n]);
	}

	return m_c;
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

int * separar_frase(int *frase, int dimension ,int inicio, int fin){

	int *matriz_b = (int *)malloc(dimension * sizeof (int));

	int pos = 0;

	while(inicio != fin){

		matriz_b[pos] = frase[inicio];
		//printf("%c",matriz_b[pos]);		
		pos++;
		inicio++;
	}
	return matriz_b;
} 

/*
int * separar_frase(int *frase, int dimension, int tamanio){

	int pos = 0;
	int pos2 = 0;

	int *matriz_b = (int *)malloc(dimension * sizeof (int));

	while(pos != tamanio){

		printf("\n[");
		for (int j = 0; j < dimension; ++j)
		{
			matriz_b[pos2] = frase[pos];
			printf("%c",matriz_b[pos2]);
			pos++;
			pos2++;
		}
		printf("]\n");
		pos2 = 0;
	}

	return matriz_b;
}*/

void print_letras(int *texto, int largo){
	
	for (int i = 0; i < largo; ++i){
			printf("%c", texto[i]);
		}
	printf("\n");
}

void print_numeros(int *texto, int largo){
	
	for (int i = 0; i < largo; ++i){
			printf("%3d ", texto[i]);
		}
	printf("\n");
}

void print_matriz(int **A, int fil, int col){
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
}

int main(int argc, char *argv[])
{
	if (argc != 4){
		printf("\n[Requiere Indicar]$ dimension m,a,t,r,i,z %cfrase%c\n", '"', '"');
		printf("Programa terminado.\n\n");
		return 1;
	}

	int *B;
	int **A;
	int i = 0;
	int x = 0;
	int tam_frase = 0;
	int *frase_formateada;
	int dim = atoi(argv[1]);

	int inicio = 0;
	
	char *frase = argv[3];
	char *matriz = argv[2];

	A = leer_matriz(A , dim, dim, matriz);

	frase_formateada = formato_frase(frase, dim);

	printf("%s\n",frase);
	print_matriz(A, dim, dim);

	while (frase_formateada[tam_frase] != '\0'){
		printf("%c", frase_formateada[tam_frase]);
		tam_frase++;
	}
	printf("\n");

	for (int i = 0; i < (tam_frase/dim); i++)
	{
			B = separar_frase(frase_formateada, dim , i*dim , (i*dim) + dim);
			print_letras(B, dim);	
	}
	printf("\n");

	//B = separar_frase(frase_formateada, dim, tam_frase);

	validar_alfabeto(frase_formateada);

	for (int i = 0; i < (tam_frase/dim); i++)
	{
			B = separar_frase(frase_formateada, dim , i*dim , (i*dim) + dim);
			print_numeros(B, dim);	
	}

	//separar_frase(frase_formateada, dim, tam_frase);
/*
	while (x < i){
		printf("( ");
		for (int i = 0; i < dim; ++i)
		{
			printf("%d ", frase_formateada[x++]);
		}
		printf(") ");
	}
	printf("\n");
*/
	int matB[3] = {2,14,12};

//	mult_matriz(A, matB, dim);


	return 0;
}