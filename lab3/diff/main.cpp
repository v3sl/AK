#include <iostream>
#include <omp.h>
#include <cmath>
#include <string>
#include <vector>
#include <stdio.h>

#define PI 3.14159265358979323846

double a = 0;
double b = 2;
int n;
std::vector<double> F;

double f(int k, double h)
{
    if (F[k] == INT_MIN)
    {
        if (a + k * h <= PI / 2)
        {
            F[k] = std::cos(a + k * h);
        }
        else
        {
            F[k] = PI / 2 - a - k * h;
        }
        return F[k];
    }
    else
    {
        return F[k];
    }
}

int main(int argc, char **argv)
{
    std::cin >> n;
    int n2 = 4 * n;
    double h = (b - a) / n;
    double h2 = (b - a) / n2;
    F = std::vector<double>(n2 + 2, INT_MIN);
    std::vector<double> rez(n + 1);
    std::vector<double> rez2(n2 + 1);
    std::vector<double> ideal(n + 1);
    std::vector<double> ideal2(n2 + 1);

#pragma omp parallel
    {
#pragma omp sections
        {
#pragma omp section
            {
#pragma omp for
                for (int i = 0; i < n + 1; i++){
                    rez[i] = (f(i + 1, h) - f(i, h)) / h;
}
#pragma omp for
for (int i = 0; i < n + 1; i++)
{
    if (a + h * i <= PI / 2)
    {
        ideal[i] = -std::sin(a + h * i);
    }
    else
    {
        ideal[i] = -1;
    }
}
}
#pragma omp section
{
#pragma omp for
    for (int i = 0; i < n2 + 1; i++)
    {
        rez2[i] = (f(i + 1, h2) - f(i, h2)) / h2;
    }
#pragma omp for
    for (int i = 0; i < n2 + 1; i++)
    {
        if (a + h2 * i <= PI / 2)
        {
            ideal2[i] = -std::sin(a + h2 * i);
        }
        else
        {
            ideal2[i] = -1;
        }
    }
}
}
}

#pragma omp single
{
    std::cout << "N\n";
    for (int i = 0; i < rez.size(); i++)
    {
        std::cout << "k = " << i << " : " << rez[i] << " ideal: " << ideal[i] << " difference: " << std::abs(rez[i] - ideal[i]) << '\n';
    }
    std::cout << "\n\n4N\n";
    for (int i = 0; i < rez2.size(); i++)
    {
        std::cout << "k = " << i << " : " << rez2[i] << " ideal: " << ideal2[i] << " difference: " << std::abs(rez2[i] - ideal2[i]) << '\n';
    }
}
}