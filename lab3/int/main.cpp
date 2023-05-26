#include <iostream>
#include <omp.h>
#include <cmath>
#include <string>
#include <vector>
#include <stdio.h>

#define PI 3.14159265358979323846

double a = 0;
double b = 1;
double h;
int n;

double f(int k)
{
    return (a + k * h) * (a + k * h) - 2 * (a + k * h);
}

int main(int argc, char **argv)
{
    std::cin >> n;
    h = (b - a) / n;
    double ideal = double(-2) / 3;
    double sum = 0;
#pragma omp parallel
    {
#pragma omp for
        for (int i = 1; i < n; i++)
        {
#pragma omp critical
            {
                sum += f(i);
            }
        }
    }

#pragma omp single
    {
        std::cout << sum * h << "  "
                  << " " << ideal << " E(f) = " << sum * h - ideal;
    }
}