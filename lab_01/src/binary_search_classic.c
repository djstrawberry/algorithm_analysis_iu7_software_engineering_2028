#include "search_algorithms.h"

ssize_t binary_search_classic(const int *arr, size_t size, int standart)
{
    size_t left = 0, right = size;
    while (left < right)
    {
        size_t median = left + (right - left) / 2;
        if (arr[median] < standart)
            left = median + 1;
        else if (arr[median] > standart)
            right = median;
        else
            return median;
    }
    return -1;
}

search_result_t binary_search_classic_extra(const int *arr, size_t size, int standart)
{
    search_result_t result = {-1, 0, 0};
    size_t left = 0, right = size;
    while (left < right)
    {
        result.comparisons++;
        size_t median = left + (right - left) / 2;
        if (arr[median] < standart)
            left = median + 1;
        else if (arr[median] > standart)
            right = median;
        else
        {
            result.index = median;
            return result;
        }
    }
    return result;
}