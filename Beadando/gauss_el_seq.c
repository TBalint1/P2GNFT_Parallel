#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#define N 100

int random_number(int start, int end)
{
    int number;

    number = rand() % (end + 1 - start) + start;

    return number;
}

void Gauss_Elimination(float a[N + 1][N + 1], float x[N])
{
    float ratio;

    for (int i = 1; i <= N - 1; i++)
    {
        if (a[i][i] == 0.0)
        {
            printf("Error!");
            return;
        }
        for (int j = i + 1; j <= N; j++)
        {
            ratio = a[j][i] / a[i][i];

            for (int k = 1; k <= N + 1; k++)
            {
                a[j][k] = a[j][k] - ratio * a[i][k];
            }
        }
    }

    x[N - 1] = a[N][N + 1] / a[N][N];

    for (int i = N - 2; i >= 0; i--)
    {
        x[i] = a[i + 1][N + 1];
        for (int j = i + 1; j < N; j++)
        {
            x[i] = x[i] - a[i + 1][j + 1] * x[j];
        }
        x[i] = x[i] / a[i + 1][i + 1];
    }

    printf("\nA megoldas:\n");
    for (int i = 0; i < N; i++)
    {
        printf("x[%d] = %0.3f\n", i + 1, x[i]);
    }
}

int main()
{
    float a[N + 1][N + 1], x[N], sum;
    clock_t start, end;
    double time_spent;

    start = clock();

    printf("Random szamok generalasa:\n");

    srand(time(NULL));

    for (int i = 1; i <= N; i++)
    {
        sum = 0.0;
        for (int j = 1; j <= N; j++)
        {
            a[i][j] = random_number(-10, 10);
            sum += a[i][j];
            printf("a[%d][%d]= %f\n", i, j, a[i][j]);
        }
        a[i][N + 1] = sum + random_number(1, 10);
        printf("a[%d][%d]= %f\n", i, N + 1, a[i][N + 1]);
    }

    Gauss_Elimination(a, x);

    end = clock();

    time_spent = (double)(end - start) / CLOCKS_PER_SEC;
    printf("A szamitas ideje: %f sec.", time_spent);

    return 0;
}
