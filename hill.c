/*
	Asignatura: Computo de alto desempeño
	Semestre: 2019-2

	Cifrado Hill
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <omp.h>

#define LETRAS 26

int alfabeto[] = {'A','B','C','D','E','F','G','H','I','J','K','L','M',
				'N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};

char * leer_archivo(FILE *file, char *inputFileName){
	size_t maxl = 256;
	char *line = malloc(maxl * sizeof(char));
	
	if(!line){
    	printf("La memoria no se reservo!!\n");
    	exit(-2);
	}

	if ( (file = fopen(inputFileName, "r")) == NULL){
		printf("No se puede leer el archivo.\n");
		exit(1);
	}

	while (fgets(line, maxl, file)) {

    	while(line[strlen(line) - 1] != '\n' && line[strlen(line) - 1] != '\r'){
        	char *tmp = realloc (line, 2 * maxl * sizeof(char));

        	fseek(file,0,SEEK_SET);
        	if (tmp) {
            	line = tmp;
            	maxl *= 2;
            	fgets(line, maxl, file);
        	}
        	else{
            	printf("No hay suficiente memoria para esta linea!!\n");
            	exit(-3);
        	}
    	}
	}
	return line;
}

void print_mensaje(FILE *file_cifrado,int *m, int elementos){

	for (int i = 0; i < elementos; i++)
	{
		printf("%c", alfabeto[m[i]]);
		fprintf(file_cifrado, "%c" , alfabeto[m[i]]);
	}
}

int * modulo_hill(int *m, int elementos){

	for (int i = 0; i < elementos; ++i)
	{
		if ( m[i] < 0)
			m[i] = LETRAS + (m[i]%LETRAS);
		else if ( m[i] == -LETRAS)
			m[i] = 0;
		else
			m[i] = m[i]%LETRAS;
	}
	return m;
}

int * mult_matriz(int **m_a, int *m_b, int dimension){

	int *m_c = (int *)calloc(dimension, sizeof(int));

	for (int i = 0; i < dimension; i++)
	{
		for (int j = 0; j < dimension; j++)
		{
			m_c[i] = m_c[i] + ( m_a[i][j] * m_b[j] );
		}
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
				token = strtok(NULL, ",");
			}
		}
	}
	return matriz_a;
}

int * formato_frase(char *str_original, int n){
	/*Quita espacios y caracteres especiales*/
	int modulo;
	int relleno;
	int pos = 0;
	int pos2 = 0;
	int largo = strlen(str_original);
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

	modulo = pos2 % n;
	relleno = n - modulo;

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
		pos++;
		inicio++;
	}
	return matriz_b;
}

void print_letras(int *texto, int largo){
	
	for (int i = 0; i < largo; ++i){
			printf("%c", texto[i]);
		}
	printf("\n");
}

void print_numeros(int *texto, int largo){
	
	for (int i = 0; i < largo; ++i){
			printf("%2d ", texto[i]);
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

int * llenar_frase(int *frase, int *vector, int inicio, int fin){

	int pos = 0;

	while(inicio != fin){

		
		frase[inicio] = vector[pos];
		pos++;
		inicio++;
	}
	return frase;
}


int main(int argc, char *argv[])
{

	double start_time = omp_get_wtime();

	if (argc != 5){
		printf("\n[Requiere Indicar]$ dimension m,a,t,r,i,z archivo_in archivo_out\n", '"', '"');
		printf("Programa terminado.\n\n");
		return 1;
	}

	int *B;
	int *C;
	int *D;
	int **A;
	FILE *input;
	FILE *file_cifrado = fopen(argv[4],"w");
	int tam_frase = 0;
	int *frase_formateada;
	int dim = atoi(argv[1]);

	char *matriz = argv[2];
	char *frase = leer_archivo(input, argv[3]);

	int nthreads, tid;

	A = leer_matriz(A , dim, dim, matriz);

	frase_formateada = formato_frase(frase, dim);

	printf("\nFRASE LEIDA>>>\n%s",frase);
	
	printf("\nFRASE CON FORMATO>>>\n");
	while (frase_formateada[tam_frase] != '\0'){
		printf("%c", frase_formateada[tam_frase]);
		tam_frase++;
	}
	

	/*<<INICIO DE FUNCIONES INFORMATIVAS>>
	
		DESDE AQUI ESTAS FUNCIONES TIENEN CARACTER INFORMATIVO
		NO IMPORTA SI SE BORRAN, NO AFECTA AL PROGRAMA
		SOLO ESTAN PARA MOSTRAR EN PANTALLA EL PROCESO
		DEL PROGRAMA.
		(CON EXCEPCION DE LA LINEA MARCADA).
	*/

	printf("\n\nMATRIZ INGRESADA>>>\n");
	print_matriz(A, dim, dim);

	printf("\nGRUPOS DE LETRAS>>>\n");
		for (int x = 0; x < (tam_frase/dim); x++)
		{
			B = separar_frase(frase_formateada, dim , x*dim , (x*dim) + dim);
			print_letras(B, dim);	
		}

	
	validar_alfabeto(frase_formateada);	/*<<<<<<< ESTA LINEA DE CODIGO ES IMPORTANTE PARA EL PROGRAMA!!!!*/
	

	printf("\nLETRAS A NUMEROS>>>\n");
		for (int x = 0; x < (tam_frase/dim); x++)
		{
			B = separar_frase(frase_formateada, dim , x*dim , (x*dim) + dim);
			print_numeros(B, dim);	
		}

	printf("\nMULTIPLICACION DE MATRIZ VECTORES Y MODULO>>>\n");
		for (int x = 0; x < (tam_frase/dim); x++)
		{
			B = separar_frase(frase_formateada, dim , x*dim , (x*dim) + dim);
			C = mult_matriz(A,B,dim);
			modulo_hill(C,dim);
			print_numeros(C, dim);
		}

	/*<<FIN DE FUNCIONES INFORMATIVAS>>

		ANTES DE ESTE BLOQUE SOLO EXISTEN FUNCIONES
		PARA VISUALIZAR EL PROCESO DEL PROGRAMA,
		NO IMPORTAN SI SE BORRAN.
		(CON EXCEPCION DE LA LINEA MARCADA).
	*/

	printf("\nPROCESO DE PARALELIZACION>>>\n\n");

	D = calloc(tam_frase,sizeof(int));

//	#pragma omp parallel
//	{	
//		#pragma omp for

		for (int i = 0; i < (tam_frase/dim); ++i)
		{

			tid = omp_get_thread_num();
			nthreads = omp_get_num_threads();

			B = separar_frase(frase_formateada, dim , i*dim , (i*dim) + dim);
			C = mult_matriz(A,B,dim);
			modulo_hill(C,dim);
			llenar_frase(D,C,i*dim,(i*dim) + dim);
			
			/*PARA VISIALIZAR COMO TRABAJAN LOS HILOS
			  DESCOMENTE LA SIGUIENTES DOS LINEAS.*/
			//print_mensaje(file_cifrado, D, tam_frase);
			//printf("\tEl thread %d de %d threads calcula la iteracion %d\n", tid, nthreads, i); 
		}//for
//	}//join

	printf("\nFRASE CIFRADA>>>\n");	
	print_mensaje(file_cifrado, D, tam_frase);
	fprintf(file_cifrado, "\n%s" ,"<fin del archivo>");
	
	printf("\n\nARCHIVO CREADO>>>\n%s\n\n", argv[4]);

	free(B);
	free(A);
	free(C);
	free(D);
	free(frase);
	free(frase_formateada);

	double time = omp_get_wtime() - start_time;

	printf("Time %f\n", time);

	return 0;
}