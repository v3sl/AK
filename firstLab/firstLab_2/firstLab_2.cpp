#include <iostream>
#include <vector>
#include <cmath>
#include "mpi.h"

#pragma warning( disable : 6001)
#pragma warning( disable : 6385)

void FillMatrix(int* m, int numberOfElements, int l, int r)
{
    for (int i = 0; i < numberOfElements; ++i)
    {
        m[i] = rand() % (r - l + 1) + l;
    }
}

void PrintMatrix(int* m, int h, int w)
{
    for (int i = 0; i < h; ++i)
    {
        for (int j = 0; j < w; ++j)
        {
            std::cout << m[i * w + j] << " ";
        }
        std::cout << '\n';
    }
    std::cout << '\n';
}

int main(int argc, char** argv)
{
    MPI_Init(&argc, &argv);
    srand(time(NULL));
    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    const int l = 4;
    const int m = 5;
    int totalSize = l * m;
    int* firstMatrix = new int[totalSize];
    int* secondMatrix = new int[totalSize];
    if (rank == 0)
    {
        FillMatrix(firstMatrix, totalSize, 5, 9);
        FillMatrix(secondMatrix, totalSize, 0, 4);
        PrintMatrix(firstMatrix, l, m);
        PrintMatrix(secondMatrix, l, m);
    }
    MPI_Bcast(secondMatrix, totalSize, MPI_INT, 0, MPI_COMM_WORLD);
    int numberOfElements = totalSize / size;
    int remainder = totalSize % size;
    int* sendCounts = new int[size];
    int* displs = new int[size];
    int offset = 0;
    for (int i = 0; i < size; ++i)
    {
        displs[i] = offset;
        sendCounts[i] = numberOfElements;
        offset += numberOfElements;
        if (remainder > 0)
        {
            --remainder;
            ++sendCounts[i];
            ++offset;
        }
    }
    int* lines = new int[sendCounts[rank]];
    MPI_Scatterv(firstMatrix, sendCounts, displs,
        MPI_INT, lines, sendCounts[rank], MPI_INT, 0, MPI_COMM_WORLD);
    int* result = new int[sendCounts[rank]];
    for (int i = 0; i < sendCounts[rank]; ++i)
    {
        result[i] = lines[i] - (secondMatrix + displs[rank])[i];
    }
    int* joinedResult = new int[totalSize];
    MPI_Gatherv(result, sendCounts[rank],
        MPI_INT, joinedResult,
        sendCounts, displs, MPI_INT, 0, MPI_COMM_WORLD);
    if (rank == 0)
    {
        PrintMatrix(joinedResult, l, m);
    }
    delete[] firstMatrix;
    delete[] secondMatrix;
    delete[] sendCounts;
    delete[] displs;
    delete[] lines;
    delete[] result;
    delete[] joinedResult;
    MPI_Finalize();
    return 0;
}