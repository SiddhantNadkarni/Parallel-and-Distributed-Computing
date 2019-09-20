#include <iostream>
#include <pthread.h>
#include <vector>
#include <mutex>

class thread_data
{
public:
	int id;
	int* rank;
	int* output;
	int* element;
	int size;
	
};

void* arrangeArray(void* threadP)
{
	thread_data* threadT = static_cast<thread_data*>(threadP);
	int arrSize(threadT->size);
	int index(threadT->id);
	
	threadT->output[threadT->rank[index]] = threadT->element[index];
	pthread_exit(NULL);

}
std::mutex mut;
void* getRankElement(void* threadP)
{
	thread_data* threadT = static_cast<thread_data*>(threadP);
	int arrSize(threadT->size);
	int index(threadT->id);
	int count(0);
	int currElement(threadT->element[index]);

	for (int i = 0; i < arrSize; ++i)
	{
		mut.lock();
		if(currElement < threadT->element[i])
			threadT->rank[i]++;
		mut.unlock();
	}
	

	pthread_exit(NULL);
}



void printArray(int* rankIndex, int size)
{
	for (int i = 0; i < size; ++i)
	{
		std::cout << rankIndex[i] << std::endl;
	}
	pthread_exit(NULL);
}

int main(int argc, char const *argv[])
{
	int arr[5] = {4,2,1,3,5};
	pthread_attr_t  attr;
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
	int num_threads = 5;
	thread_data threadT[num_threads];
	pthread_t threads[num_threads];
	int rc;
	int rankIndex[5] = {0};
	int outputArr[num_threads];

	for (int i = 0; i < num_threads; ++i)
	{
		threadT[i].id = i;
		threadT[i].rank = rankIndex;
		threadT[i].size = num_threads;
		threadT[i].element = arr;
		rc = pthread_create(&threads[i], &attr, getRankElement, (void* )&threadT[i]);
	}

	for (int i = 0; i < num_threads; ++i)
	{
		threadT[i].id = i;
		threadT[i].rank = rankIndex;
		threadT[i].size = num_threads;
		threadT[i].output = outputArr;
		threadT[i].element = arr;
		rc = pthread_create(&threads[i], NULL, arrangeArray, (void* )&threadT[i]);
	}

	pthread_attr_destroy(&attr);


	for(int i = 0; i < 5 ; i++)
  		pthread_join(threads[i], NULL);

	// std::cout << "Printing rank array: "<< std::endl;
	// printArray(rankIndex, num_threads);		
	std::cout << "Printing outputArr array: "<< std::endl;
	printArray(outputArr, num_threads);

	pthread_exit(NULL);


	return 0;
}