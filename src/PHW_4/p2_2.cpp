#include <iostream>
#include <mpi.h>
#include <fstream>

int* getTextArray(std::string fileName)
{
	std::ifstream infile(fileName);
	std::string eachLine;
	int c(0);
	int* arrayText = new int [64];

	// while(std::getline(infile, eachLine))
	// {
	// 	arrayText[c] = stoi(eachLine);
	// 	c++;
	// }

	for (int i = 0; i < 64; ++i)
	{
		infile >> arrayText[i];
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

	int sum(0), finalSum;
	int a, b;
	int* arrayText = new int [64];
	



	if(rank == 0)
	{
		arrayText = getTextArray("number.txt");
		sum = getSum(arrayText, 0, 15);
	}

	MPI_Bcast(arrayText, 64, MPI_INT, 0, MPI_COMM_WORLD);

	

	if(rank == 1)
	{
		sum = getSum(arrayText, 16, 31);
	}

	if(rank == 2)
	{
		sum = getSum(arrayText, 32, 47); 
	}

	if(rank == 3)
	{
		sum  = getSum(arrayText, 48, 63);
	}

	MPI_Reduce(&sum, &b, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

	
	if (rank == 0)
	{
		std::cout << "Final sum: " << b << std::endl;
	}
	






	MPI_Finalize();

	delete [] arrayText;
	return 0;
}