#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <pthread.h>
#include <unistd.h>

struct prime
{
    int min, max, thread;
} typedef prime;

void *findPrime(void *args)
{

    prime *limit = args;
    int x;
    int min = limit->min;
    int max = limit->max;
    int thread = limit->thread;
    int number = 0;
    for (int i = min + 1; i < max; ++i)
    {
        x = 0;
        for (int j = 2; j <= i / 2; ++j)
        {
            if (i % j == 0)
            {
                x = 1;
                break;
            }
        }
        if (x == 0)
            number++;
    }
    printf("[%d] %d darab primszamot talaltam (%d - %d)\n", thread, number, min, max);
}

int main()
{
    pthread_t threads[10];
    prime limit[10];
    limit[0].min = 0;
    limit[0].max = 99;
    limit[0].thread = 0;

    for (int i = 0; i < 10; i++)
    {
        pthread_create(&threads[i], NULL, findPrime, &limit[i]);
        limit[i + 1].min = limit[i].max + 1;
        limit[i + 1].max = limit[i].max + 100;
        limit[i].thread = i;
    }

    for (int i = 0; i < 10; i++)
    {
        pthread_join(threads[i], NULL);
    }

    return 0;
}