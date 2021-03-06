#include <iostream>
#include <time.h>


double** allocate2DArrayA(int height, int width)
{
	double** mat = new double* [height];
	for (int i = 0; i < height; ++i)
	{
		mat[i] = new double [width];
		for (int j = 0; j < width; ++j)
		{
			mat[i][j] = i;
		}
	}

	return mat;
}

double** allocate2DArrayB(int height, int width)
{
	double** mat = new double* [height];
	for (int i = 0; i < height; ++i)
	{
		mat[i] = new double [width];
		for (int j = 0; j < width; ++j)
		{
			mat[i][j] = i+j;
		}
	}

	return mat;
}

double** allocate2DArrayC(int height, int width)
{
	double** mat = new double* [height];
	for (int i = 0; i < height; ++i)
	{
		mat[i] = new double [width];
		for (int j = 0; j < width; ++j)
		{
			mat[i][j] = 0;
		}
	}

	return mat;
}

void deallocate2DArray(double** mat, int height, int width)
{
	for (int i = 0; i < height; ++i)
	{
		delete [] mat[i];
	}

	delete [] mat;
}


int main(int argc, char const *argv[])
{
	int i, j, k;
	struct timespec start, stop; 
	double time;
	int n = 4096; // matrix size is n*n

	double** A = allocate2DArrayA(n, n);
	double** B = allocate2DArrayB(n, n);
	double** C = allocate2DArrayC(n, n);


	if( clock_gettime(CLOCK_REALTIME, &start) == -1) { perror("clock gettime");}
	

	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			for (int k = 0; k < n; ++k)
			{
				C[i][j] += A[i][k]*B[k][j];
			}
			
		}
	}
	

	
	if( clock_gettime( CLOCK_REALTIME, &stop) == -1 ) { perror("clock gettime");}		
	time = (stop.tv_sec - start.tv_sec)+ (double)(stop.tv_nsec - start.tv_nsec)/1e9;

	std::cout << "Number of FLOPs = " << 2*n*n*n << std::endl;
	std::cout << "Execution time = " << time << std::endl;
	std::cout << 1/time/1e6*2*n*n*n << " MFLOPs per sec" << std::endl;
	std::cout << "C[100][100] = " << C[100][100] << std::endl;


	deallocate2DArray(A, n, n);
	deallocate2DArray(B, n, n);
	deallocate2DArray(C, n, n);
	return 0;
}