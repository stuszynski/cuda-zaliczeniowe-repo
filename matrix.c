#include <stdio.h>
#include "timers.h"

#define ROWS 500
#define COLS 600

// gcc matrix.c -lrt


int MatrixA[ROWS][COLS];
int MatrixB[COLS][ROWS];
int MatrixC[ROWS][ROWS];


void generate(){
int i,j;
int zarodek;
zarodek= time(NULL);
srand(zarodek); 

	for ( i = 0; i < ROWS; ++i)
	{
		for ( j = 0; j < COLS; ++j)
		{
			MatrixA[i][j] = rand()%10;
			MatrixB[j][i] = rand()%10;
		}
	}
}

void printMA(){
	int i,j;
	for ( i = 0; i < ROWS; ++i)
	{
		for ( j = 0; j < COLS; ++j)
		{
			printf("%i", MatrixA[i][j]);
		}
		printf("\n");
	}	
	printf("\n");
}

void printMB(){
	int i,j;
	for ( i = 0; i < COLS; ++i)
	{
		for ( j = 0; j < ROWS; ++j)
		{
			printf("%i", MatrixB[j][i]);
		}
		printf("\n");
	}	
	printf("\n");
}

void printMC(){

	int i,j;

	for ( i = 0; i < ROWS; ++i)
	{
		for ( j = 0; j < ROWS; ++j)
		{
			printf("%i ", MatrixC[j][i]);
		}
		printf("\n");
	}	
	printf("\n");
}

void multiply(){

	int i,k,j;

		for ( i = 0; i < ROWS; ++i)
		{
			for ( k = 0; k < ROWS; ++k)
			{
				for ( j = 0; j < COLS; ++j)
				{
					MatrixC[i][k] += MatrixA[i][j] * MatrixB[j][k];
				}
			}
		}
}

int main(int argc, char const *argv[])
{
	//init timer
	pTimer czas = newTimer();
	startTimer(czas);

	//oblicznia
	generate();
	//printMA();
	//printMB();
	multiply();
	//printMC();

	//czas
	stopTimer(czas);
	printTimer(czas);
	freeTimer(czas);
	printf("\n\n");
	return 0;
}