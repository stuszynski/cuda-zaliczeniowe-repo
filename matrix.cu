#include <stdio.>
#include <cuda.h>

/* naive CUDA version */
__global__ void naiveMul( float* P, float* M, float* N, int width ) {
int tx = threadIdx.x; // current thread position
int ty = threadIdx.y; // in 2D block of threads
float sum = 0.0; // element computed by the thread

for (k = 0; k < width; k++)
	sum += M[ty*width+k] * N[k*width+tx];
P[ty*width+tx] = sum;
// element [tx,ty] is now calculated
}
...

int main(int argc, char const *argv[])
{
	dim3 blockDim( width, width );
	dim3 gridDim(1,1);
	naviveMul <<< gridDim, blockDim >>> ( P, M, N, width );
// <<< SIZE, 1 >>>
	return 0;
}



