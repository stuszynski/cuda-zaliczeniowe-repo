
// program pokazujacy dodawanie wektorow na GPU
// kompilacja:
// nvcc vecAdd.cu -o vecAdd
// w programie ZAKLADAMY, ze wektor na dlugosc 10

#include <stdio.h>
#include <cuda.h>
#define SIZE 10

__global__ void vecAdd( float*A, float*B, float*C ){
	int i = threadIdx.x;
	C[i] = A[i] + B[i];
}

int main(){

	float *hostA = (float*) malloc(SIZE*sizeof(float));
	float *hostB = (float*) malloc(SIZE*sizeof(float));
	float *hostC = (float*) malloc(SIZE*sizeof(float));
	float *devA,*devB,*devC;

	// ustawiamy wartosci wektor na hoscie na 1
	int i;
	for(i=0;i<SIZE;i++){
		hostA[i] = 1;
		hostB[i] = 1;
	}

	// robimy alokacje pamieci na GPU
	// http://pl.wikipedia.org/wiki/Alokacja_zasob%C3%B3w
	cudaMalloc( (void**) &devA, sizeof(float)*SIZE);
	cudaMalloc( (void**) &devB, sizeof(float)*SIZE);
	cudaMalloc( (void**) &devC, sizeof(float)*SIZE);

	// przesylamy dane z wektorow host do dev
	// (czyli z hostA do devA, itd)
	cudaMemcpy(devA,hostA,SIZE*sizeof(float),cudaMemcpyHostToDevice);
	cudaMemcpy(devB,hostB,SIZE*sizeof(float),cudaMemcpyHostToDevice);

	// dane sa przeslane do karty. Mamy hostA na CPU i devA na GPU
	// z CPU widac tylko wskaznik devA - ktory ma sens tylko na GPU
	// odwolania z CPU do danych wskazywanych przez devA moga zabic

	// odpalamy obliczenia na GPU, coby wykonac sumowanie wektorow
	vecAdd<<<1,SIZE>>>(devA,devB,devC);

	// po obliczeniach, nalezy sume wektorow WYSLAC z powrotem do CPU
	// czyli do wektora hostC
	cudaMemcpy(hostC,devC,SIZE*sizeof(float),cudaMemcpyDeviceToHost);

	// teraz trzeba wypisac, czy sie zsumowalo. Bo inaczej mozna tylko gdybac.
	// suma wektorow rownych 1 powinna wynosic 2 w kazdym elemencie.

	printf("SUMA hostC = ");
	for(i=0;i<SIZE;i++)	printf(" %1.f",hostC[i]);
	printf("\n");

	// zwalnianie pamieci wczesniej zaalokowanej
	free(hostA);free(hostB);free(hostC);
	cudaFree(devA);cudaFree(devB);cudaFree(devC);
}


