#include <stdlib.h>
#include <stdio.h>
#include <cublas.h>
#include <time.h>
#include <iostream>

#define size 1024

__global__ void matrixMul(int *a, int *b, int *c){
	int my_x, my_y;
	my_x = blockIdx.x*blockDim.x + threadIdx.x;	
	my_y = blockIdx.y*blockDim.y + threadIdx.y;
	int local_c = 0;
	for(int i = 0 ; i < size; i++)
		local_c += a[my_x * size + i] * b[i * size + my_y];
	
	c[my_x * size + my_y ] = local_c;

}


int main(int argc, char const *argv[])
{
	int n = 1024;
	struct timespec start, stop; 
    double time;
	int* a = (int*)malloc(sizeof(int)*n*n);
	int* b = (int*)malloc(sizeof(int)*n*n);
	int* c = (int*)malloc(sizeof(int)*n*n);

	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			a[i*n + j] = 1;
			b[i*n + j] = 2;
			c[i*n + j] = 0;
		}
	}

	int *gpu_a, *gpu_b, *gpu_c;
	cudaMalloc((void**)&gpu_a, sizeof(int)*n*n);
	cudaMalloc((void**)&gpu_b, sizeof(int)*n*n);
	cudaMalloc((void**)&gpu_c, sizeof(int)*n*n);

	cudaMemcpy(gpu_a, a, sizeof(int)*n*n, cudaMemcpyHostToDevice);
	cudaMemcpy(gpu_b, b, sizeof(int)*n*n, cudaMemcpyHostToDevice);

	dim3 dimGrid(64, 64);
	dim3 dimBlock(16, 16);

	if(clock_gettime(CLOCK_REALTIME, &start) == -1 ) 
	{ 
		perror( "clock gettime" );
	}

	matrixMul<<<dimGrid, dimBlock>>>(gpu_a, gpu_b, gpu_c);				
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