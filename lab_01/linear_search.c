#include "linear_search.h"

ssize_t linear_search(int *arr, size_t size, int standart)
{
    if (!arr)
        return -1;
    for (size_t i = 0; (i < size); ++i)
    {
        if (arr[i] == standart)
            return i;
    }
    return -1;
}