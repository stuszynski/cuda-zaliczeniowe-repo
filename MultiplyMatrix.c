#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ROWS 5
#define COLS 10

int MatrixA[ROWS][COLS];

void genMatrix(int **matrix, int x, int y){

int zarodek;
zarodek= time(NULL);
srand(zarodek); 

int i, j;
	for(i = 0; i < x; i++)
		{
		for(j = 0; j < y; j++)
			matrix[i][j] = 0;
		}
}
void printM(int **matrix, int x, int y){

for (int i = 0; i < x; ++i)
{
	for (int j = 0; j < y; ++j)
	{
		printf("%i\n", matrix[x][y]);
	}
}

}

int main(int argc, char const *argv[])
{
	
	
	genMatrix(&&MatrixA, ROWS,COLS);

	printM(&&MatrixA,ROWS,COLS);

	return 0;
}