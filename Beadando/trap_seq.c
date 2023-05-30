
#include <stdio.h>
#include <conio.h>
#include <math.h>
#include <time.h>

#define f(x) 1 / (1 + pow(x, 2))

void trap_method(float lower, float upper, int subInterval)
{

    float stepSize, k;
    float integration = 0.0;

    stepSize = (upper - lower) / subInterval;

    integration = f(lower) + f(upper);
    for (int i = 1; i <= subInterval - 1; i++)
    {
        k = lower + i * stepSize;
        integration = integration + 2 * f(k);
    }
    integration = integration * stepSize / 2;
    printf("\nAz integráció szükséges értéke: %.3f", integration);
}

int main()
{
    float lower, upper, integration = 0.0, stepSize, k;
    int i, subInterval;

    printf("Az integrálás alsóhatára: ");
    scanf("%f", &lower);
    printf("Az integrálás felsőhatára: ");
    scanf("%f", &upper);
    printf("Részintervallumok száma: ");
    scanf("%d", &subInterval);

    clock_t start, end;
    double time_spent;

    start = clock();

    trap_method(lower, upper, subInterval);

    end = clock();

    time_spent = (double)(end - start) / CLOCKS_PER_SEC;
    printf("\nA szamitas ideje: %f sec.", time_spent);

    return 0;
}
