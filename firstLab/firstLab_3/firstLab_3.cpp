#include <iostream>
#include <string>
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
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    int k = std::stoi(argv[argc - 3]);
    int l = std::stoi(argv[argc - 2]);
    int m = std::stoi(argv[argc - 1]);
    int firstMatrixSize = k * l;
    int secondMatrixSize = l * m;
    int* a = new int[firstMatrixSize];
    int* b = new int[secondMatrixSize];
    if (rank == 0)
    {
        FillMatrix(a, firstMatrixSize, -1, 0);
        FillMatrix(b, secondMatrixSize, -1 ,0);
        PrintMatrix(a, k, l);
        PrintMatrix(b, l, m);
    }
    MPI_Bcast(b, secondMatrixSize, MPI_INT, 0, MPI_COMM_WORLD);
    int rowsforProcess = k / size;
    int remainder = k % size;
    int* sendCounts = new int[size];
    int* displs = new int[size];
    int* sendCountsRec = new int[size];
    int* displsRec = new int[size];
    int offset = 0;
    int offsetRec = 0;
    for (int i = 0; i < size; ++i)
    {
        displs[i] = offset;
        displsRec[i] = offsetRec;
        sendCounts[i] = rowsforProcess * l;
        sendCountsRec[i] = rowsforProcess * m;
        offsetRec += rowsforProcess * m;
        offset += rowsforProcess * l;
        if (remainder > 0)
        {
            --remainder;
            sendCounts[i] += l;
            sendCountsRec[i] += m;
            offset += l;
            offsetRec += m;

        }
    }
    int* proc = new int[sendCounts[rank]];
    MPI_Scatterv(a, sendCounts, displs, MPI_INT, proc, sendCounts[rank], MPI_INT, 0, MPI_COMM_WORLD);
    int* tempRes = new int[m * sendCounts[rank] / l];
    for (int i = 0; i < m * sendCounts[rank] / l; ++i)
    {
        tempRes[i] = 0;
    }
    int count = 0;
    for (int i = 0; i < sendCounts[rank] / l; ++i)
    {
        for (int j = 0; j < m; ++j)
        {
            for (int p = 0; p < l; ++p)
            {
                tempRes[i * m + j] += proc[i * l + p] * b[p * m + j];
            }
        }
    }
    int* result = new int[k * m];
    MPI_Gatherv(tempRes, sendCountsRec[rank],
        MPI_INT, result,
        sendCountsRec, displsRec, MPI_INT, 0, MPI_COMM_WORLD);
    if (rank == 0)
    {
        PrintMatrix(result, k, m);
    }
    MPI_Finalize();
    return 0;
}