#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
    int i;
    int amount = 10;
    int start = 1;
    int end = 20;
    int numbers[amount];

    printf("\nGenerating %d Random Numbers between %d and %d:\n", amount, start, end);
    srand(time(0));
    for (i = 0; i < amount; i++)
    {
        numbers[i] = rand() % (end + 1 - start) + start;
        printf("%d\n", numbers[i]);
    }

    FILE *fp;

    fp = fopen("numbers.txt", "wt");
    if (!fp)
    {
        printf("Error: cannot open file.");
        return;
    }

    for (i = 0; i < amount; i++)
    {

        fprintf(fp, "%d , ", numbers[i]);
    }

    fclose(fp);

    getch();
    return 0;
}