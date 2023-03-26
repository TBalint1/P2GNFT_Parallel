#include <stdio.h>
#include <time.h>

int main()
{

    int num, i, count, n;
    printf("Enter max range: ");
    scanf("%d", &n);
    clock_t t;
    t = clock();
    t = clock() - t;

    for (num = 1; num <= n; num++)
    {

        if (num % 1000 == 0)
        {

            printf("\n");
            double time_taken = ((double)t) / CLOCKS_PER_SEC;
            printf("At %d : %f seconds to execute \n", num, time_taken);
        }

        count = 0;

        for (i = 2; i <= num / 2; i++)
        {
            if (num % i == 0)
            {
                count++;
                break;
            }
        }

        if (count == 0 && num != 1)
        {
            printf("%d ", num);
        }
    }
    return 0;
}
