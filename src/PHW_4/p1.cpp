#include <iostream>
#include <mpi.h>




int main(int argc, char *argv[])
{
	int size, rank;

	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Status status;

	int msg(0);
	
	if(rank == 0)
	{
		if(msg == 0)
		{
			msg = 451;
		    std::cout << "Process 0: Initially Msg = " << msg << std::endl;
		    MPI_Send(&msg, 1, MPI_INT, 1, 200, MPI_COMM_WORLD);
		}

		else
			MPI_Recv(&msg, 1, MPI_INT, 3, 200, MPI_COMM_WORLD, &status);

	}

	if(rank == 1)
	{
		MPI_Recv(&msg, 1, MPI_INT, 0, 200, MPI_COMM_WORLD, &status);
		++msg;
		std::cout << "Process 1: Initially Msg = " << msg << std::endl;
		MPI_Send(&msg, 1, MPI_INT, 2, 200, MPI_COMM_WORLD);
	}


	if(rank == 2)
	{
		MPI_Recv(&msg, 1, MPI_INT, 1, 200, MPI_COMM_WORLD, &status);
		++msg;
		std::cout << "Process 2: Initially Msg = " << msg << std::endl;
		MPI_Send(&msg, 1, MPI_INT, 3, 200, MPI_COMM_WORLD);
	}



	if(rank == 3)
	{
		MPI_Recv(&msg, 1, MPI_INT, 2, 200, MPI_COMM_WORLD, &status);
		++msg;
		std::cout << "Process 3: Initially Msg = " << msg << ". Done!" << std::endl;
		MPI_Send(&msg, 1, MPI_INT, 0, 200, MPI_COMM_WORLD);
	}

	MPI_Finalize();

	return 0;
}