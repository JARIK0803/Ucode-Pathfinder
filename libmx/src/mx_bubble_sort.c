#include "../inc/libmx.h"

int mx_bubble_sort(char **arr, int size)
{
    int noSwap;
    char *tmp;
    int swap = 0;

    for (int i = 0; i < size - 1; i++)
    {
        noSwap = 1;

        for (int j = 0; j < size - 1 - i; j++)
        {
            if (mx_strcmp(arr[j], arr[j + 1]) > 0)
            {
                tmp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = tmp;
                noSwap = 0;
                swap++;
            }
        }

        if (noSwap == 1)
        {
            break;
        }
    }
    
    return swap;
}
