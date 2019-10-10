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

	// for(itr = cluster.begin(); itr != cluster.end(); itr++)
	// {
	// 	sum += itr->second;
	// 	// std::cout << sum << std::endl;
	// }

	sum = boost::accumulate(cluster | boost::adaptors::map_values, 0);

	return sum/cluster.size();
}


unsigned char* getFinalOutput(unsigned char* Image1DOutput, std::unordered_map<int, int> cluster, 
	int height, int width, int mean)
{
	std::unordered_map<int, int>::iterator itr;

	for(itr = cluster.begin(); itr != cluster.end(); itr++)
	{
		Image1DOutput[itr->first] = mean;
	}

	return Image1DOutput;
}


unsigned char* getKMeansClustered(unsigned char* Image1D, int height, int width)
{
	int iters(30);
	int mean1(0), mean2(85), mean3(170), mean4(255), pixel; 

	unsigned char* Image1DOutput = new unsigned char[height*width];
	std::unordered_map<int, int> cluster1, cluster2, cluster3, cluster4;
	std::vector<int> minDist(4, 0);

	while(iters>0)
	{
		cluster1.clear();
		cluster2.clear();
		cluster3.clear();
		cluster4.clear();
		for (int i = 0; i < height; ++i)
		{
			for (int j = 0; j < width; ++j)
			{
				pixel = Image1D[i*width + j];


				minDist[0] = (int(abs(pixel - mean1)));

				minDist[1] = (int(abs(pixel - mean2)));

				minDist[2] = (int(abs(pixel - mean3)));

				minDist[3] = (int(abs(pixel - mean4)));

				int min_pos = std::distance(minDist.begin(), std::min_element(minDist.begin(),minDist.end()));


				switch(min_pos)
				{
					case 0:
					cluster1[i*width + j] = pixel;
					break;

					case 1:
					cluster2[i*width + j] = pixel;
					break;

					case 2:
					cluster3[i*width + j] = pixel;
					break;

					case 3:
					cluster4[i*width + j] = pixel;
					break;
				}
			}
		}


		iters--;
		mean1 = getMeanOfCluster(cluster1);
		mean2 = getMeanOfCluster(cluster2);
		mean3 = getMeanOfCluster(cluster3);
		mean4 = getMeanOfCluster(cluster4);

		// std::cout << "Means are: " << mean1 << ", " << mean2 << ", " << mean3 << ", " << mean4 << ", " << "; Iter: " << iters << std::endl;
	}



	Image1DOutput = getFinalOutput(Image1DOutput, cluster1, h, w, mean1);
	Image1DOutput = getFinalOutput(Image1DOutput, cluster2, h, w, mean2);
	Image1DOutput = getFinalOutput(Image1DOutput, cluster3, h, w, mean3);
	Image1DOutput = getFinalOutput(Image1DOutput, cluster4, h, w, mean4);

	return Image1DOutput;


}



int main(int argc, char const *argv[])
{
	struct timespec start, stop;
	unsigned char* Image1D = readImage(argv[1], h, w, 1); 
	std::cout << "Image read" << std::endl;
	

	if(clock_gettime(CLOCK_REALTIME, &start) == -1) 
		perror("clock gettime");

	unsigned char* Image1DOutput = getKMeansClustered(Image1D, h, w);

	if(clock_gettime( CLOCK_REALTIME, &stop) == -1 )
		perror("clock gettime");


	double time = (stop.tv_sec - start.tv_sec)+ (double)(stop.tv_nsec - start.tv_nsec)/1e9;
	std::cout << "time taken: " << time << std::endl;

	
	saveImage(output_file, Image1DOutput, h, w, 1);
	delete [] Image1D;
	delete [] Image1DOutput;


	return 0;
}