#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void genMatrix(int **matrix, int x, int y){

int i, zarodek;
zarodek= time(NULL);
srand(zarodek); 

for (int i = 0; i < x; ++i)
{
	for (int j = 0; j < y; ++j)
	{
		**matrix[x][y] = rand()%100;
	}
}
}
void printM(int Matrix[3][2], int x, int y){

for (int i = 0; i < x; ++i)
{
	for (int j = 0; j < y; ++j)
	{
		printf("%i\n", Matrix[x][y]);
	}
}

}

int main(int argc, char const *argv[])
{
	
	

	int MatrixA[3][2];
	genMatrix(&&MatrixA, 3,2);

	printM(MatrixA,3,2);

	return 0;
}