#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <omp.h>

#define AMOUNT 7

int randomNumber(int amount, int start, int end)
{

    int number = rand() % (end + 1 - start) + start;
    return number;
}

int sequintal(int *numbers)
{
    int x = 1;

    for (int i = 0; i < AMOUNT; i++)
    {
        x = x * numbers[i];
    }

    return x;
}

int openMP_Parallel(int *numbers)
{
    int x = 1;

#pragma omp parallel for
    for (int i = 0; i < AMOUNT; i++)
    {
        x = x * numbers[i];
    }

    return x;
}

int openMP_Reduction(int *numbers)
{
    int x = 1;

#pragma omp parallel for reduction(* \
                                   : x);
    for (int i = 0; i < AMOUNT; i++)
    {
        x = x * numbers[i];
    }

    return x;
}

int main()
{

    int start = 1;
    int end = 10;
    int numbers[AMOUNT];
    printf("\nEgy %d elemu tomb generalasa %d es %d kozott.\n", AMOUNT, start, end);
    srand(time(0));
    for (int i = 0; i < AMOUNT; i++)
    {

        numbers[i] = randomNumber(AMOUNT, start, end);
        printf("%d ; ", numbers[i]);
    }

    printf("\nA tomb szorzata szekvenciálisan: %d", sequintal(numbers));

    printf("\nA tomb szorzata OpenMP for ciklus hasznalataval: %d", openMP_Parallel(numbers));

    printf("\nA tomb szorzata OpenMP redukcios operator hasznalataval: %d", sequintal(numbers));

    return 0;
}