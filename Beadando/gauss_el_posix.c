#include <stdio.h>
#include <math.h>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>

#define N 100
#define NUMBER_OF_THREADS 2

struct ThreadData
{
    float (*a)[N + 1];
    float *x;
    int thread_id;
};

pthread_mutex_t mutex;

int random_number(int start, int end)
{
    int number;

    number = rand() % (end + 1 - start) + start;

    return number;
}

void *eliminate(void *arg)
{
    struct ThreadData *data = (struct ThreadData *)arg;
    int thread_id = data->thread_id;
    float ratio;

    for (int i = thread_id + 1; i <= N - 1; i += NUMBER_OF_THREADS)
    {
        if (data->a[i][i] == 0.0)
        {
            printf("Error!");
            return NULL;
        }

        pthread_mutex_lock(&mutex);

        for (int j = i + 1; j <= N; j++)
        {
            ratio = data->a[j][i] / data->a[i][i];

            for (int k = 1; k <= N + 1; k++)
            {
                data->a[j][k] = data->a[j][k] - ratio * data->a[i][k];
            }
        }

        pthread_mutex_unlock(&mutex);
    }

    return NULL;
}

void Gauss_Elimination(float a[N + 1][N + 1], float x[N])
{
    pthread_t threads[NUMBER_OF_THREADS];
    struct ThreadData thread_data[NUMBER_OF_THREADS];

    for (int i = 0; i < NUMBER_OF_THREADS; i++)
    {
        thread_data[i].thread_id = i;
        thread_data[i].a = a;
        thread_data[i].x = x;
    }

    pthread_mutex_init(&mutex, NULL);

    for (int i = 0; i < NUMBER_OF_THREADS; i++)
    {
        for (int j = 1; j <= N; j++)
        {
            for (int k = 1; k <= N + 1; k++)
            {
                thread_data[i].a[j][k] = a[j][k];
            }
        }
    }

    for (int i = 0; i < NUMBER_OF_THREADS; i++)
    {
        pthread_create(&threads[i], NULL, eliminate, (void *)&thread_data[i]);
    }

    for (int i = 0; i < NUMBER_OF_THREADS; i++)
    {
        pthread_join(threads[i], NULL);
    }

    pthread_mutex_destroy(&mutex);

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

    printf("\nAz eredmeny:\n");
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
