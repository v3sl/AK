#include <iostream>
#include <string>
#include "mpi.h"
#include <vector>

#pragma warning( disable : 6001)
#pragma warning( disable : 6385)

void FillMatrix(std::vector<int>& m, int numberOfElements, int l, int r)
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
    int k = std::stoi(argv[1]);
    int l = std::stoi(argv[2]);
    int m = std::stoi(argv[3]);
    std::vector<int> a;
    std::vector<int> b(l * m);
    if (rank == 0)
    {
        a.resize(k * l);
        FillMatrix(a, k * l, -1, 0);
        FillMatrix(b, l * m, -1, 0);
        //PrintMatrix(a.data(), k, l);
        //PrintMatrix(b.data(), l, m);
    }
    MPI_Bcast(b.data(), l * m, MPI_INT, 0, MPI_COMM_WORLD);
    int rowsforProcess = k / size;
    int remainder = k % size;
    std::vector<int>sendCounts(size);
    std::vector<int>displs(size);
    std::vector<int>sendCountsRec(size);
    std::vector<int>displsRec(size);
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
    std::vector<int> proc(sendCounts[rank]);
    MPI_Scatterv(a.data(), sendCounts.data(), displs.data(), MPI_INT, proc.data(), sendCounts[rank], MPI_INT, 0, MPI_COMM_WORLD);
    std::vector<int> tempRes(sendCounts[rank] / l * m);
    for (int i = 0; i < sendCounts[rank] / l; ++i)
    {
        for (int j = 0; j < m; ++j)
        {
            int sumRes = 0;
            for (int p = 0; p < l; ++p)
            {
                sumRes += proc[i * l + p] * b[p * m + j];
            }
            tempRes[i * m + j] = sumRes;
        }
    }
    std::vector<int> result(k * m);
    MPI_Gatherv(tempRes.data(), sendCountsRec[rank],
        MPI_INT, result.data(),
        sendCountsRec.data(), displsRec.data(), MPI_INT, 0, MPI_COMM_WORLD);
    if (rank == 0)
    {
        //PrintMatrix(result.data(), k, m);
    }
    MPI_Finalize();
    return 0;
}