#include <iostream>
#include <time.h>
#include <omp.h>

#define		size	   16*1024*1024

int* allocateArray()
{
	int* array = new int [size];

	for (int i = 0; i < size; ++i)
	{
		array[i] = size - i;
	}

	return array;
}

void swap(int* x, int* y)
{
	int temp = *x;
	*x = *y;
	*y = temp;
}

int partition(int* array, int start, int end)
{
	srand(time(NULL));
	int randIndex(start + rand()%(end - start)); 
	int pivot(array[randIndex]);
	swap(&array[randIndex], &array[end]);
	int i(start - 1);
	// #pragma omp parallel for
	for (int j = start; j < end; ++j)
	{
		if(array[j] <= pivot)
		{
			i++;
			swap(&array[i], &array[j]);
		}
	}

	swap(&array[i+1], &array[end]);
	return (i+1);

}

void quickSort(int *array, int start, int end)
{

	if(start < end)
	{
		int partElement = partition(array, start, end);
		quickSort(array, start, partElement - 1);	
		quickSort(array, partElement + 1, end);
	}


}

int main(void){
	int i, j, tmp;
	struct timespec start, stop; 
	double exe_time;
	int* m = allocateArray();
	
	if( clock_gettime(CLOCK_REALTIME, &start) == -1) { perror("clock gettime");}

	int partElement = partition(m, 0, size - 1);
	omp_set_num_threads(2);


	#pragma omp parallel sections
	{
		#pragma omp section
		{
			quickSort(m, 0, partElement -1);
		}

		#pragma omp section
		{
			quickSort(m, partElement + 1, size - 1);
		}
	}

	if( clock_gettime( CLOCK_REALTIME, &stop) == -1 ) { perror("clock gettime");}		
	exe_time = (stop.tv_sec - start.tv_sec)+ (double)(stop.tv_nsec - start.tv_nsec)/1e9;
	
	for(i=0;i<16;i++) printf("%d ", m[i]);		
	printf("\nExecution time = %f sec\n",  exe_time);
	delete [] m;
	return 0;		
}	