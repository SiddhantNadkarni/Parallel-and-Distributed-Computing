#include <iostream>
#include <mpi.h>
#include <fstream>

int* getTextArray(std::string fileName)
{
	std::ifstream infile(fileName);
	std::string eachLine;
	int c(0);
	int* arrayText = new int [64];

	while(std::getline(infile, eachLine))
	{
		arrayText[c] = stoi(eachLine);
		c++;
	}
	infile.close();

	return arrayText;
}

int getSum(int* arrayText, int startIndex, int endIndex)
{
	int sum(0);
	for (int i = startIndex; i <= endIndex; ++i)
	{
		sum+= arrayText[i];
	}

	return sum;
}


int main(int argc, char *argv[])
{
	int size, rank;
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Status status;
	int sum, sumFinal;
	int* a = new int [1];
	int* finalSum = new int [4];
	int* arrayText = new int [64];
	int* arrayText2 = new int [16];
	



	if(rank == 0)
	{
		arrayText = getTextArray("number.txt");
		
	}

	MPI_Scatter(arrayText, 16, MPI_INT, arrayText2, 16, MPI_INT, 0, MPI_COMM_WORLD);

	if (rank == 0)
	{
		a[0] = getSum(arrayText2, 0, 15);
	}
	

	if(rank == 1)
	{

		a[0] = getSum(arrayText2, 0, 15);

	}

	if(rank == 2)
	{

		a[0] = getSum(arrayText2, 0, 15);

	}

	if(rank == 3)
	{

		a[0] = getSum(arrayText2, 0, 15);
	}

	MPI_Gather(a, 1, MPI_INT, finalSum, 1, MPI_INT, 0, MPI_COMM_WORLD);

	if(rank == 0)
	{
		sumFinal = finalSum[0] + finalSum[1] + finalSum[2] + finalSum[3];
		std::cout << "Final sum: " << sumFinal << std::endl;
	}


	MPI_Finalize();

	delete [] arrayText;
	delete [] finalSum;
	delete [] a;
	return 0;
}