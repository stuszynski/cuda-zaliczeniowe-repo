#include <stdio.h>

#define ROWS 5
#define COLS 8

int MatrixA[ROWS][COLS];
int MatrixB[COLS][ROWS];
int MatrixC[ROWS][ROWS];


void generate(){

int zarodek;
zarodek= time(NULL);
srand(zarodek); 

	for (int i = 0; i < ROWS; ++i)
	{
		for (int j = 0; j < COLS; ++j)
		{
			MatrixA[i][j] = rand()%10;
			MatrixB[j][i] = rand()%10;
		}
	}
}

void printMA(){
	for (int i = 0; i < ROWS; ++i)
	{
		for (int j = 0; j < COLS; ++j)
		{
			printf("%i", MatrixA[i][j]);
		}
		printf("\n");
	}	
	printf("\n");
}

void printMB(){
	for (int i = 0; i < COLS; ++i)
	{
		for (int j = 0; j < ROWS; ++j)
		{
			printf("%i", MatrixB[j][i]);
		}
		printf("\n");
	}	
	printf("\n");
}

void multiply(){
	
	for (int i = 0; i < ROWS; ++i)
	{
		for (int j = 0; j < ROWS; ++j)
		{
			for (int a = 0; a < ROWS; ++a)
			{
				for (int k = 0; k < COLS; ++k)
				{
					MatrixC[i][j] += MatrixA[a][k] * MatrixB[k][a] 
				}
			}
		}
	}
}

int main(int argc, char const *argv[])
{
	generate();
	printMA();
	printMB();
	return 0;
}