#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_SIZE 2500
#define BILLION  1000000000L;
// gcc matrix.c -lrt



int *generate(int rozmiar){
	int zarodek;
    zarodek= time(NULL);
    srand(zarodek);   // za zarodek wstawiamy pobrany czas w sekundach

    int *a = (int*)calloc(rozmiar*rozmiar, sizeof(int));
    int i,j;
    for(i=0;i<rozmiar;i++)
        for(j=0;j<rozmiar;j++)
            a[i*rozmiar+j] = rand()%10;
    return a;
}



int *multiply(int *A, int *B, int rozmiar) {

	int i,k,j;
	int *wynik = (int*)calloc(rozmiar*rozmiar, sizeof(int));
	for ( i = 0; i < rozmiar; ++i)
	{
		for ( k = 0; k < rozmiar; ++k)
		{
			for ( j = 0; j < rozmiar; ++j)
			{
				wynik[i*rozmiar+j] += A[i*rozmiar+j] * B[j*rozmiar+i];
			}
		}
	}

	return wynik;
}


void printMat(int *a, int width) {
    int i,j;
    for(i=0;i<width;i++) 
        for(j=0;j<width;j++)
            printf("%d%c",a[i*width+j],(j == (width-1))?'\n':'\t');
    printf("\n");
}


void oblicz (int rozmiar){
	//generowanie macierzy
	
	int *MatrixA = generate(rozmiar);
    int *MatrixB = generate(rozmiar);

	//timer!
	struct timespec start, stop;
	double accum;

	if( clock_gettime( CLOCK_REALTIME, &start) == -1 ) {
		perror( "clock gettime" );
		return EXIT_FAILURE;
	}
//-------------------------------------
	int *MatrixC = multiply(MatrixA,MatrixB,rozmiar);
//--------------------------------


	if( clock_gettime( CLOCK_REALTIME, &stop) == -1 ) {
		perror( "clock gettime" );
		return EXIT_FAILURE;
	}
		accum = ( stop.tv_sec - start.tv_sec )
		+ (double)( stop.tv_nsec - start.tv_nsec )
		/ (double)BILLION;
		printf("Dla macierzy o rozmiarach = %i : ", rozmiar);
		printf( "%lf ms \n", accum * 1000 );

		free(MatrixA);
		free(MatrixB);
		free(MatrixC);

}

int main(int argc, char const *argv[])
{
		
		//seria powtórzeń 
   	int i;
    for ( i = 1; i < 2500; ++i) if (i%100 == 0) {
      oblicz(i);
    

}

		return 0;
	}