#include <stdio.h>
#include <conio.h>
#include <math.h>
#include <time.h>
#include <omp.h>

#define f1(x, y, z) (17 - y + 2 * z) / 20
#define f2(x, y, z) (-18 - 3 * x + z) / 20
#define f3(x, y, z) (25 - 2 * x + 3 * y) / 20

void Gauss_Seidel(float e)
{
    float x0 = 0, y0 = 0, z0 = 0, x1, y1, z1, e1, e2, e3;
    int count = 1;

    printf("\nCount\tx\ty\tz\n");

    do
    {

#pragma omp parallel
        {
#pragma omp for
            for (int i = 0; i < 1; i++)
            {
                x1 = f1(x0, y0, z0);
                y1 = f2(x1, y0, z0);
                z1 = f3(x1, y1, z0);
            }
        }

        printf("%d\t%0.4f\t%0.4f\t%0.4f\n", count, x1, y1, z1);

        e1 = fabs(x0 - x1);
        e2 = fabs(y0 - y1);
        e3 = fabs(z0 - z1);

        count++;

        x0 = x1;
        y0 = y1;
        z0 = z1;

    } while (e1 > e && e2 > e && e3 > e);

    printf("\nA megoldas: x=%0.3f, y=%0.3f and z = %0.3f\n", x1, y1, z1);
}

int main()
{
    float e;
    clock_t start, end;
    double time_spent;
    printf("Elfogadhato hibak:\n");
    scanf("%f", &e);

    start = clock();

    Gauss_Seidel(e);

    end = clock();

    time_spent = (double)(end - start) / CLOCKS_PER_SEC;
    printf("A szamitas ideje: %f sec.", time_spent);

    return 0;
}
