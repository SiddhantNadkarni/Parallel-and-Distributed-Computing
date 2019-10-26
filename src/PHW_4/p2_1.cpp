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
	int sum0(0), sum1(0), sum2(0), sum3(0), finalSum(0);
	



	if(rank == 0)
	{
		int* arrayText = getTextArray("number.txt");
		sum0 = getSum(arrayText, 0, 15);
		MPI_Recv(&sum1, 1, MPI_INT, 1, 201, MPI_COMM_WORLD, &status);
		MPI_Recv(&sum2, 1, MPI_INT, 2, 202, MPI_COMM_WORLD, &status);
		MPI_Recv(&sum3, 1, MPI_INT, 3, 203, MPI_COMM_WORLD, &status);
		finalSum = sum0 + sum1 + sum2 + sum3;
		std::cout << "Final sum: " << finalSum << std::endl;

	}

	if(rank == 1)
	{
		int* arrayText = getTextArray("number.txt");
		sum1 = getSum(arrayText, 16, 32);
		MPI_Send(&sum1, 1, MPI_INT, 0, 201, MPI_COMM_WORLD);
	}

	if(rank == 2)
	{
		int* arrayText = getTextArray("number.txt");
		sum2 = getSum(arrayText, 33, 47); //32 or 33
		MPI_Send(&sum2, 1, MPI_INT, 0, 202, MPI_COMM_WORLD);
	}

	if(rank == 3)
	{
		int* arrayText = getTextArray("number.txt");
		sum3 = getSum(arrayText, 48, 63);
		MPI_Send(&sum3, 1, MPI_INT, 0, 203, MPI_COMM_WORLD);
	}




	MPI_Finalize();

	return 0;
}