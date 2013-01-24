#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ROWS 5
#define COLS 10

int matrixA[ROWS][COLS];

void genMatrix(){

int zarodek;
zarodek= time(NULL);
srand(zarodek); 

	int row, col;
        for (row = 0; row < ROWS; row++)
        {
            for (col = 0; col < COLS; col++)
            {
                matrixA[row][col] = rand()%10;
            }
        }

}

void printM(){
	
	printf("Macierz A: \n");
	int row, col;
        for (row = 0; row < ROWS; row++)
        {
            for (col = 0; col < COLS; col++)
            {
               printf("%i", matrixA[row][col]);
            }
            printf("\n");
        }

}


int main(int argc, char const *argv[])
{
	
	
	genMatrix();

	printM();

	return 0;
}