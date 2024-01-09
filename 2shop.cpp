#include <stdio.h>
#include <omp.h>
#include <iostream>
using namespace std;
int main()
{
    int sec = 4, r, i, j, lsum = 0, sum = 0;
    int id;

    printf("enter the number of items of each section\n");
    scanf("%d", &r);
    int arr[sec][r];
    for (i = 0; i < sec; i++)
    {
        for (j = 0; j < r; j++)
        {
            arr[i][j] = 0;
        }
    }
    for (i = 0; i < sec; i++)
    {
        for (j = 0; j < r; j++)
        {
            arr[i][j] = rand() % 100;
        }
    }
// lsum=0;
#pragma omp parallel
    {

        for (int i = 0; i < sec; i++)
        {
            for (int j = 0; j < r; j++)
            {
                lsum += arr[i][j];
            }
        }
        id = omp_get_thread_num();
        printf("the thread sum of thread %d is %d\n", id, lsum);

#pragma omp critical
        {
            sum += lsum;
        }
    }
    printf("the total sum is %d", sum);
}