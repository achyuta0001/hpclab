#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <omp.h>
using namespace std;
int main()
{
    int num, i;
    printf("Enter the number of steps : ");
    scanf("%d", &num);
    double step = 1.0 / (double)num, pi = 0.0;
    omp_set_num_threads(num);
#pragma omp parallel for reduction(+ : pi)
    for (i = 0; i < num; i++)
    {
        double x = (i + 0.5) * step;
        double local_pi = (4.0 * step) / (1 + x * x);
        pi += local_pi;
    }

    printf("Value of Pi = %.16lf\n", pi);
}