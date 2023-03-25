#include <ctime>
#include <fstream>
#include <vector>
#include <iostream>
#include <cmath>

std::vector<int> RandomCyclicPermutation(int length)
{
    std::vector<int> result(length);
    std::vector<int> unusedIndexes(length - 1);
    for (int i = 0; i < length - 1; ++i)
    {
        unusedIndexes[i] = i + 1;
    }
    int currentIndex = 0;
    for (int i = 0; i < length - 1; ++i)
    {
        int r = (rand() % (INT_MAX - INT_MIN)) + INT_MIN % unusedIndexes.size();
        int nextInd = unusedIndexes[r];
        unusedIndexes[r] = unusedIndexes[unusedIndexes.size() - 1];
        unusedIndexes.pop_back();
        result[currentIndex] = nextInd;
        currentIndex = nextInd;
    }
    return result;
}


double BenchmarkLatency(int sizeBytes, int iterations)
{
    std::vector<int> array = RandomCyclicPermutation(sizeBytes / 4);
    int pointer = 0;
    auto start = clock();
    for(int i = 0; i < iterations; ++i)
    {
        pointer = array[pointer];
    }
    auto end = clock();
    return (double)(end - start) / CLOCKS_PER_SEC * 1000000000 / iterations;
}

int main()
{
    std::ofstream out("data.txt");
    for (double i = 5000.0; i < 20000000.0; i *= 1.2)
    {
        //std::cout << i << ' ' << BenchmarkLatency((int)i,  100000000) << '\n';
        out << (int)i << ' ' << BenchmarkLatency((int)i,  100000000) << '\n';
    }
    return 0;
}