#include <iostream>
#include <time.h>
#include <pthread.h>
class thread
{
public:
	int id;
	double** a;
	double** b;
	double** c;
	int startIndex, endIndex;
	int n;
	
};


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


void* matMultiply(void* threadP)
{
	thread* threadT = static_cast<thread*>(threadP);
	int startIndex(threadT->startIndex);
	int endIndex(threadT->endIndex);
	int n(threadT->n);
	double** A(threadT->a);
	double** B(threadT->b);
	double** C =threadT->c;
	for (int i = 0; i < n; ++i)
	{
		for (int j = startIndex; j < endIndex; ++j)
		{
			for (int k = 0; k < n; ++k)
			{
				C[i][j] = C[i][j] + A[i][k]*B[k][j];
			}
			
		}
	}
	pthread_exit(NULL);
	
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


	int p(atoi(argv[1]));
	thread threadT[p];
	int rc, endIndex;
	int startIndex;
	pthread_t threads[p];


	if( clock_gettime(CLOCK_REALTIME, &start) == -1) { perror("clock gettime");}
	

	for (int i = 0; i < p; ++i)
	{
		startIndex = i*n/p;
		endIndex = startIndex + n/p - 1;
		threadT[i].id = i;
		threadT[i].startIndex = startIndex;
		threadT[i].endIndex = endIndex;
		threadT[i].a = A;
		threadT[i].b = B;
		threadT[i].c = C;
		threadT[i].n = n;
		rc = pthread_create(&threads[i], NULL, matMultiply, (void *)&threadT[i]);
	}

	for(int i = 0; i < p ; i++)
	{
  		pthread_join(threads[i], NULL);
	}
	
	if( clock_gettime( CLOCK_REALTIME, &stop) == -1 ) { perror("clock gettime");}		
	time = (stop.tv_sec - start.tv_sec)+ (double)(stop.tv_nsec - start.tv_nsec)/1e9;

	std::cout << "Number of FLOPs = " << 2*n*n*n << std::endl;
	std::cout << "Execution time = " << time << std::endl;
	std::cout << 1/time/1e6*2*n*n*n << " MFLOPs per sec" << std::endl;
	std::cout << "C[100][100] = " << double(C[100][100]) << std::endl;
	// printf("Execution time = %f sec,\n%lf MFLOPs per sec\n", time, 1/time/1e6*2*n*n*n);		
	// printf("C[100][100]=%f\n", C[100][100]);

	
	deallocate2DArray(A, n, n);
	deallocate2DArray(B, n, n);
	deallocate2DArray(C, n, n);

	pthread_exit(NULL);
	return 0;
}