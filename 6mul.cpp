#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <iostream>
using namespace std;
int main()
{
    int m, n, p, q;
    printf("Enter the size of 1st matrix : ");
    scanf("%d%d", &m, &n);
    printf("Enter the size of 2nd matrix : ");
    scanf("%d%d", &p, &q);
    if (n != p)
    {
        printf("Multiplication is not possible.\n");
        exit(0);
    }
    int i = 0, j = 0, k = 0;
    int arr1[m][n];
    int arr2[p][q];
    int res[m][q];
    omp_set_num_threads(m);
#pragma omp parallel private(j)
    {
#pragma omp for
        for (i = 0; i < m; i++)
        {

            for (j = 0; j < n; j++)
                arr1[i][j] = rand() % 100;
            res[i][j] = 0;
        }
    }
    omp_set_num_threads(p);
#pragma omp parallel private(j)
    {
#pragma omp for
        for (i = 0; i < p; i++)
        {

            for (j = 0; j < q; j++)
                arr2[i][j] = rand() % 100;
        }
    }
    omp_set_num_threads(m);
#pragma omp parallel private(j, k)
    {
#pragma omp for
        for (i = 0; i < m; i++)
        {
            for (j = 0; j < q; j++)
            {
                res[i][j] = 0;
                for (k = 0; k < n; k++)
                    res[i][j] += arr1[i][k] * arr2[k][j];
            }
        }
    }
    /*printf("Matrix-1 :\n");
    for(i=0;i<m;i++) {
        for(j=0;j<n;j++)
            printf("%3d ",arr1[i][j]);
        printf("\n");
    }
    printf("Matrix-2 :\n");
    for(i=0;i<p;i++) {
        for(j=0;j<q;j++)
            printf("%3d ",arr2[i][j]);
        printf("\n");
    }*/
    printf("Resultant Matrix :\n");
    for (i = 0; i < m; i++)
    {
        for (j = 0; j < q; j++)
            printf("%6d ", res[i][j]);
        printf("\n");
    }
}