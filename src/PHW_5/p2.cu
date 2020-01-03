#include <stdlib.h>
#include <stdio.h>
#include <cublas.h>
#include <time.h>
#include <iostream>
#define size 1024
#define block_size 32


__global__ void matrixMulOptimized(int* a, int* b, int* c)
{


	
	__shared__ float a_share[32][32];
	__shared__ float b_share[32][32];

	int n = 1024;
	int row = blockDim.y*blockIdx.y + threadIdx.y;
	int col = blockDim.x*blockIdx.x + threadIdx.x;

	int local_c = 0;
	for (int i = 0; i < 32; ++i)
	{
		a_share[threadIdx.y][threadIdx.x] = a[row*n + i*blockDim.y + threadIdx.x];
		b_share[threadIdx.y][threadIdx.x] = b[(i*blockDim.x + blockIdx.y)*n + col];

		__syncthreads();
		for (int k = 0; k < 32; ++k)
		{
			local_c += a_share[threadIdx.y][k]*b_share[k][threadIdx.x];
		}
		__syncthreads();
		
	}

	c[row*n + col] = local_c;
}


int main(int argc, char const *argv[])
{
	int n = 1024;
	struct timespec start, stop; 
    double time;
	int* a = (int*)malloc(sizeof(int)*n*n);
	int* b = (int*)malloc(sizeof(int)*n*n);
	int* c = (int*)malloc(sizeof(int)*n*n);

	for (int i=0; i<size*size; i++)
	{
		a[i]=1;
		b[i]=2;
		c[i]=0;			
	}

	int *gpu_a, *gpu_b, *gpu_c;
	cudaMalloc((void**)&gpu_a, sizeof(int)*n*n);
	cudaMalloc((void**)&gpu_b, sizeof(int)*n*n);
	cudaMalloc((void**)&gpu_c, sizeof(int)*n*n);

	cudaMemcpy(gpu_a, a, sizeof(int)*n*n, cudaMemcpyHostToDevice);
	cudaMemcpy(gpu_b, b, sizeof(int)*n*n, cudaMemcpyHostToDevice);

	dim3 dimGrid(32,32);
	dim3 dimBlock(32,32);


	if(clock_gettime(CLOCK_REALTIME, &start) == -1 ) 
	{ 
		perror( "clock gettime" );
	}

	matrixMulOptimized<<<dimGrid, dimBlock>>>(gpu_a, gpu_b, gpu_c);				
	cudaMemcpy(c, gpu_c, sizeof(int)*n*n, cudaMemcpyDeviceToHost);
	
	if(clock_gettime(CLOCK_REALTIME, &stop) == -1 ) 
	{ 
		perror( "clock gettime" );
	} 

	time = (stop.tv_sec - start.tv_sec)+ (double)(stop.tv_nsec - start.tv_nsec)/1e9;
	printf("time is %f ns\n", time*1e9);	
	
	std::cout << c[451*n + 451] << std::endl;

	free(a);
	free(b);
	free(c);
	cudaFree(gpu_a);
	cudaFree(gpu_b);
	cudaFree(gpu_c);
	return 0;
}