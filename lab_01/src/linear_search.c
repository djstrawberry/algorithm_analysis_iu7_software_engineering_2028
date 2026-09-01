#include "search_algorithms.h"

ssize_t linear_search(const int *arr, size_t size, int standart)
{
    for (size_t i = 0; (i < size); ++i)
    {
        if (arr[i] == standart)
            return i;
    }
    return -1;
}

search_result_t linear_search_extra(const int *arr, size_t size, int standart)
{
    search_result_t result = {-1, 0};
    for (size_t i = 0; (i < size); ++i)
    {
        result.comparisons++;
        if (arr[i] == standart)
        {
            result.index = i;
            return result;
        }
    }
    return result;
}