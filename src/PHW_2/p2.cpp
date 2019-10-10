#include <iostream>
#include <math.h>
#include <fstream>
#include <time.h>
#include <boost/range/numeric.hpp>
#include <boost/range/adaptor/map.hpp>
#include <unordered_map>
#include <algorithm>
#include <vector>
#include <iterator>

#define h  800 
#define w  800

#define output_file "output.raw"

unsigned char* readImage(const char *image, int height, int width, int bpp)
{

	unsigned char* Imagedata = new unsigned char [height*width*bpp];

	FILE *file;
	if (!(file=fopen(image,"rb"))) {
		std::cout << "Cannot open file: " << image << std::endl;
		exit(1);
	}
	fread(Imagedata, sizeof(unsigned char), height*width*bpp, file);
	fclose(file);

	return Imagedata;
}

void saveImage(const char* image, unsigned char* Imagedata, int height, int width, int bpp)
{
	FILE *file;

	if (!(file=fopen(image,"wb"))) {
		std::cout << "Cannot open file: " << image << std::endl;
		exit(1);
	}
	fwrite(Imagedata, sizeof(unsigned char), height*width*bpp, file);
	fclose(file);

	std::cout << "Filed Saved Succesfully" << std::endl;
}


int getEuclideanDist(int pixel, int mean)
{
	return abs(pixel - mean);
}

int getMeanOfCluster(std::unordered_map<int, int> cluster)
{
	std::unordered_map<int, int>::iterator itr;
	int sum(0);

	sum = boost::accumulate(cluster | boost::adaptors::map_values, 0);

	return sum/cluster.size();
}


class thread
{
public:
	
	int id;
	int startIndex;
	int endIndex;

	int* mean1;
	int* mean2;
	int* mean3;
	int* mean4;
	int* mean5;
	int* mean6;
	int numOfClusters;
	std::vector<std::vector <int> > *sum;
	std::vector<std::vector <int> > *no;
	unsigned char* Image1D;
	
};


void* K_MeansMultithreaded(void* threadP)
{
	thread* threadT = static_cast<thread*>(threadP);
	int id = threadT->id;
	int k(threadT->numOfClusters);
	std::vector<int> minDist(k, 0);
	unsigned char* Image1D = threadT->Image1D;
	int* mean1(threadT->mean1);
	int* mean2(threadT->mean2);
	int* mean3(threadT->mean3);
	int* mean4(threadT->mean4);
	int* mean5(threadT->mean5);
	int* mean6(threadT->mean6);
	int startIndex(threadT->startIndex);
	int endIndex(threadT->endIndex);
	std::vector<std::vector <int> > &sum = *threadT->sum;
	std::vector<std::vector <int> > &no = *threadT->no;

	 

	 for (int i = 0; i < h; ++i)
	 {
	 	for (int j = startIndex; j < endIndex; ++j)
	 	{

			int pixel = Image1D[i*w + j];
			


			minDist[0] = (int(abs(pixel - *mean1)));
			minDist[1] = (int(abs(pixel - *mean2)));
			minDist[2] = (int(abs(pixel - *mean3)));
			minDist[3] = (int(abs(pixel - *mean4)));
			minDist[4] = (int(abs(pixel - *mean5)));
			minDist[5] = (int(abs(pixel - *mean6)));

			int min_pos = std::distance(minDist.begin(), std::min_element(minDist.begin(),minDist.end()));
		
			sum[id][min_pos] += pixel;
			no[id][min_pos] += 1;

	    }	
	 }
	 pthread_exit(NULL);


}

struct meanValues
{
	int mean1;
	int mean2;
	int mean3;
	int mean4;
	int mean5;
	int mean6;
};


unsigned char* getFinalOutput(unsigned char* Image1D, std::vector<int> means, int numOfClusters)
{

	std::vector<int> minDist(numOfClusters, 0);
    unsigned char* Image1DOutput = new unsigned char[h*w];
    int pixel, min_pos;
	for (int i = 0; i < h; ++i)
	{
		for (int j = 0; j < w; ++j)
		{
			pixel = Image1D[i*w + j];

			minDist[0] = (int(abs(pixel - means[0])));
			minDist[1] = (int(abs(pixel - means[1])));
			minDist[2] = (int(abs(pixel - means[2])));
			minDist[3] = (int(abs(pixel - means[3])));
			minDist[4] = (int(abs(pixel - means[4])));
			minDist[5] = (int(abs(pixel - means[5])));

			min_pos = std::distance(minDist.begin(), std::min_element(minDist.begin(),minDist.end()));
			Image1DOutput[i*w + j] = means[min_pos];

		}
	}

	return Image1DOutput;
}



int main(int argc, char const *argv[])
{
	struct timespec start, stop;
	unsigned char* Image1D = readImage(argv[1], h, w, 1); 
	std::cout << "Image read 1" << std::endl;
	int p = atoi(argv[1]);
	thread threadT[p];
	int rc, startIndex, endIndex;
	pthread_t threads[p];

	unsigned char* Image1DOutput = nullptr;


	std::vector<int> means(6, 0);
	means[0] = 0;
	means[1] = 65;
	means[2] = 100;
	means[3] = 125;
	means[4] = 190;
	means[5] = 255;


	

	if(clock_gettime(CLOCK_REALTIME, &start) == -1) 
		perror("clock gettime");



	for (int k = 0; k < 50; ++k)
	{
	std::vector<std::vector <int> > sum(p, std::vector<int>(6,0));
	std::vector<std::vector <int> > no(p, std::vector<int>(6,0));
		for (int i = 0; i < p; ++i)
		{
			startIndex = i*h/p;
		    endIndex = startIndex + h/p - 1;
		    threadT[i].startIndex = startIndex;
		    threadT[i].endIndex = endIndex;
			threadT[i].numOfClusters = 6;
			threadT[i].id = i;
			threadT[i].mean1 = &means[0];
			threadT[i].mean2 = &means[1];
			threadT[i].mean3 = &means[2];
			threadT[i].mean4 = &means[3];
			threadT[i].mean5 = &means[4];
			threadT[i].mean6 = &means[5];
			threadT[i].Image1D = Image1D;
			threadT[i].sum = &sum;
			threadT[i].no = &no;


			rc = pthread_create(&threads[i], NULL, K_MeansMultithreaded, (void *)&threadT[i]);
		}





		for(int i = 0; i < p ; i++)
	    {
	    	pthread_join(threads[i], NULL);
	    }

		for (int i = 0; i < 6; ++i)
		{
			int sumAll(0);
			int lengthAll(0);
			for (int j = 0; j < p; ++j)
			{
				sumAll += sum[j][i];
				lengthAll += no[j][i];
			}

			means[i] = sumAll/lengthAll;
		}

		sum.clear();
		no.clear();

	}

	std::cout << "Means are: " << means[0] << ", " << means[1] << ", " << means[2] << ", " << means[3] << ", " << means[4] << ", " << means[5] << std::endl;

	Image1DOutput = getFinalOutput(Image1D, means, 6);


	if(clock_gettime( CLOCK_REALTIME, &stop) == -1 )
		perror("clock gettime");


	double time = (stop.tv_sec - start.tv_sec)+ (double)(stop.tv_nsec - start.tv_nsec)/1e9;
	std::cout << "time taken: " << time << std::endl;

	
	saveImage(output_file, Image1DOutput, h, w, 1);
	delete [] Image1D;
	delete [] Image1DOutput;
	pthread_exit(NULL);


	return 0;
}