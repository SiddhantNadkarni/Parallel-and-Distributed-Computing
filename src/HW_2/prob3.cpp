#include <iostream>
#include <pthread.h>
#include <mutex>


class thread
{
 public:
 	int id;
	int src;
	int dest;
	int weight;
	int* value;
	bool* flag;
};

std::mutex mut;

void* bellmanFordAlgo(void* threadT2)
{
	thread* threadT = static_cast<thread*>(threadT2);
	int index(threadT->id);
	int src(threadT->src);
	int dest(threadT->dest);
	int W(threadT->weight);
	int* val = threadT->value;
	bool* flag(threadT->flag);
	mut.lock();

	if(val[src] + W < val[dest])
	{
		val[dest] = val[src] + W;
		*flag = true;
	}

	mut.unlock();
	pthread_exit(NULL);
}

int main(int argc, char const *argv[])
{
	int num_threads = 5;
	pthread_t threads[num_threads];
	thread threadT[5];
	int sources[5] = {0, 0, 3, 1, 3};
	int dests[5] = {1, 3, 1, 2, 2};
	int weights[5] = {1, 3, 4, 5, 2};
	int value[4] = {0, INT_MAX, INT_MAX, INT_MAX};
	bool flag = true;
	int rc;


	//Intialize threads and pass them to bellmanFordAlgo function
	for (int i = 0; i < num_threads; i++)
	{
		threadT[i].id = i;
		threadT[i].src = sources[i];
		threadT[i].dest = dests[i];
		threadT[i].weight = weights[i];
		threadT[i].flag = &flag;
		threadT[i].value = value;
		rc = pthread_create(&threads[i], NULL, bellmanFordAlgo, (void *)&threadT[i]);
	}


	//Join threads
	for(int i = 0; i < num_threads ; i++)
	{
  		pthread_join(threads[i], NULL);
	}

	//print array containing shortest paths
	for (int i = 0; i < 4; ++i)
	{
		std::cout << value[i] << std::endl;
	}

	pthread_exit(NULL);
	return 0;
}



