#include <stdio.h>
#include <omp.h>
#include <iostream>
using namespace std;
int main()
{
    int i, j, n;
    printf("enter the number of students in the list\n");
    scanf("%d", &n);
    double arr[n], arr_m = 0;

    for (i = 0; i < n; i++)
    {
        arr[i] = (double)(rand() % 100) / 10;
    }
    int id = omp_get_thread_num();
    printf("the cgpa of students of thread %d is :", id);
    for (i = 0; i < n; i++)
        printf("%.2lf \t", arr[i]);
    printf("\n");
#pragma omp parallel for
    for (i = 0; i < n; i++)
    {
#pragma omp critical
        if (arr_m < arr[i])
            arr_m = arr[i];
    }
    printf("Student with highest CGPA = %.2lf\n", arr_m);
}