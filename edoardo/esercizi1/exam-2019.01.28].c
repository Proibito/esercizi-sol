#include <stdio.h>

int range_of_even(int *nums, int length, int *min, int *max)
{
    int k = 0;
    for (k; k < length; k++)
    {
        printf("%d", nums[k] == 0);
        if (nums[k] % 2 == 0 || nums[k] == 0)
        {
            *min = nums[k];
            *max = nums[k];
            break;
        }
    }
    k = 0;

    for (k; k < length; k++)
    {
        int *numeroAttuale = nums;
        if (*numeroAttuale % 2 == 0)
        {
            if (*numeroAttuale > *max)
            {
                *max = *numeroAttuale;
            }

            if (*numeroAttuale < *min)
            {
                *min = *numeroAttuale;
            }
        }
        nums = nums + 1;
    }
    if (*max % 2 == 1 || *min % 2 == 1)
    {
        return 0;
    }
}

int main()
{
    int numeri[] = {501, 3, 50, 30, 21, 333, 321};
    int min, max;
    int ritorno = range_of_even(&numeri, sizeof(numeri) / sizeof(*numeri), &min, &max);
    printf("ritorno: %d, min: %d, max: %d", ritorno, min, max);
}