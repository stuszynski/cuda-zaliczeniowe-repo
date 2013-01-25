#include <stdio.h>
#include <cuda.h>
#include <stdlib.h>
#include <ctype.h>

#define TILE_SIZE 2
#define MAX_SIZE 2500


__global__ void MatrixMulShared(int *M, int *N, int *P, int width) {

  __shared__ int sharedM[TILE_SIZE][TILE_SIZE];
  __shared__ int sharedN[TILE_SIZE][TILE_SIZE];

  int bx = blockIdx.x;
  int by = blockIdx.y;
  int tx = threadIdx.x;
  int ty = threadIdx.y;

  int row = by * TILE_SIZE + ty;
  int col = bx * TILE_SIZE + tx;

  int sum = 0;

  for(int m = 0; m < width/TILE_SIZE; m++) {
    sharedM[ty][tx] = M[row*width + (m*TILE_SIZE + tx)];
    sharedN[ty][tx] = N[(m*TILE_SIZE + ty)*width + col];

    __syncthreads();

    for(int k = 0; k < TILE_SIZE; k++) {
      sum += sharedM[m+ty][k] * sharedN[k][m+tx]; 
    }
    __syncthreads();
  }
  P[row*width+col] = sum; 
}


void printMat(int *a, int width) {
    int i,j;
    for(i=0;i<width;i++) 
        for(j=0;j<width;j++)
            printf("%d%c",a[i*width+j],(j == (width-1))?'\n':'\t');

    printf("\n");
}


int* generatorMatrixa(int width) {
    int zarodek;
    zarodek= time(NULL);
    srand(zarodek);   // za zarodek wstawiamy pobrany czas w sekundach

    int *a = (int*)calloc(width*width, sizeof(int));
    int i,j;
    for(i=0;i<width;i++)
        for(j=0;j<width;j++)
            a[i*width+j] = rand()%10;
    return a;
}


int *matMul(int *hostA, int *hostB, int width) {

    cudaEvent_t start, stop;
    float time;
    cudaEventCreate(&start);
    cudaEventCreate(&stop);


    int SIZE = width*width;
    int *hostC = (int*)calloc(SIZE,sizeof(int));

    int *devA, *devB, *devC;
    cudaMalloc((void**) &devA, SIZE*sizeof(int));
    cudaMalloc((void**) &devB, SIZE*sizeof(int));
    cudaMalloc((void**) &devC, SIZE*sizeof(int));

       dim3 gridDim(width/TILE_SIZE, width/TILE_SIZE);
       dim3 blockDim(TILE_SIZE,TILE_SIZE);
    cudaMemcpy(devA, hostA, SIZE*sizeof(int), cudaMemcpyHostToDevice);
    cudaMemcpy(devB, hostB, SIZE*sizeof(int), cudaMemcpyHostToDevice);
    cudaMemcpy(devC, hostC, SIZE*sizeof(int), cudaMemcpyHostToDevice);


       cudaEventRecord(start, 0); //rozpoczecie pomiaru czasu
       MatrixMulShared<<<gridDim,blockDim>>>(devA, devB, devC, width); //AKCJA!
       cudaEventRecord(stop, 0); // koniec pomiaru
       cudaEventSynchronize(stop); // synchro

    cudaMemcpy(hostC, devC, SIZE*sizeof(int), cudaMemcpyDeviceToHost);
    cudaEventElapsedTime(&time, start, stop);
    printf ("Czas trwania: %f ms\n", time);

    cudaFree(devA);cudaFree(devB);cudaFree(devC);
    return hostC;
}

void oblicz(int Rozmiar){

    int rozmiar = Rozmiar;
    int *A = generatorMatrixa(rozmiar);
    int *B = generatorMatrixa(rozmiar);

    //inicjalizacja i jednoczesne obliczenia macierzy.
    printf("Dla macierzy rozmiarów  =  %i ", rozmiar);
    int *C = matMul(A,B,rozmiar);
 
    //printf("\n");
    //printMat(C,m);
   
    free(A);
    free(B);
    free(C);
}


int main() {
    
    //seryjka 
    int i;
    for ( i = 0; i < MAX_SIZE; ++i) if (i%100 == 0) {
      oblicz(i);
    }
    
   
    return 0;

}