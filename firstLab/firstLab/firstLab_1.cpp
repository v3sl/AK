#include <iostream>
#include <string>
#include "mpi.h"

#pragma warning( disable : 6001)
#pragma warning( disable : 6385)

void FillVector(int* v, int size)
{
	for (int i = 0; i < size; ++i)
	{
		v[i] = rand() % 2 - 1;
	}
}

void PrintVector(int* v, int size)
{
	for (int i = 0; i < size; ++i)
	{
		std::cout << v[i] << ' ';
	}
	std::cout << '\n';
}

int main(int argc, char** argv)
{
	MPI_Init(&argc, &argv);
	srand(time(NULL));
	int rank, size;
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	int length = std::stoi(argv[argc - 1]);
	int lengthForProcess = length / size;
	int remainder = length % size;
	int* a = new int[length];
	int* b = new int[length];
	int* a1 = new int[length];
	int* b1 = new int[length];
	int result = 0, processResult = 0;
	if (rank == 0)
	{
		FillVector(a, length);
		FillVector(b, length);
		PrintVector(a, length);
		PrintVector(b, length);
	}
	int* displs = new int[size];
	int* sendCounts = new int[size];
	int offset = 0;
	for (int i = 0; i < size; ++i)
	{
		displs[i] = offset;
		sendCounts[i] = lengthForProcess;
		offset += lengthForProcess;
		if (remainder > 0)
		{
			++sendCounts[i];
			++offset;
			--remainder;
		}
	}
	MPI_Scatterv(a, sendCounts, displs, MPI_INT, a1, sendCounts[rank], MPI_INT, 0, MPI_COMM_WORLD);
	MPI_Scatterv(b, sendCounts, displs, MPI_INT, b1, sendCounts[rank], MPI_INT, 0, MPI_COMM_WORLD);
	for (int i = 0; i < sendCounts[rank]; i++)
	{
		if (rank < length)
		{
			processResult += a1[i] * b1[i];
		}
	}
	MPI_Reduce(&processResult, &result, 1, MPI_INT, MPI_SUM,0, MPI_COMM_WORLD);
	if (rank == 0)
	{
		std::cout << result << '\n';
	}
	delete[] a;
	delete[] a1;
	delete[] b;
	delete[] b1;
	delete[] displs;
	delete[] sendCounts;
	MPI_Finalize();
	return 0;
}