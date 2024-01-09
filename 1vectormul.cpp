#include <stdio.h>
#include <iostream>
#include <omp.h>
#include <vector>
using namespace std;
int main()
{
    int n, i, j;
    cout << "enter the value of n";
    cin >> n;
    int a[n][n], res[n];
    int x[n];
    omp_set_num_threads(n);
#pragma omp parallel private(j)
    {
        for (i = 0; i < n; i++)
        {
            for (j = 0; j < n; j++)
            {
                a[i][j] = rand() % 100;
                x[j] = rand() % 100;
                res[j] = 0;
            }
        }
    }
#pragma omp parallel private(j)
    {
        for (i = 0; i < n; i++)
        {
            for (j = 0; j < n; j++)
            {
                res[j] = a[i][j] * x[j];
            }
        }
    }
    cout << "the matrix\n";

    for (j = 0; j < n; j++)
    {
        cout << res[j];
        cout << "\n";
    }
}