#include "binary_searches.h"

size_t bit_floor(size_t size);
size_t bit_ceil(size_t size);
int compare(int a, int b);

ssize_t binary_search_v1(int *arr, size_t size, int standart)
{
    if (!arr)
        return -1;
    size_t left = 0, right = size;
    while (left < right)
    {
        size_t median = (left + right) / 2;
        if (arr[median] < standart)
            left = median + 1;
        else if (arr[median] > standart)
            right = median;
        else
            return median;
    }
    return -1;
}

// branchless
ssize_t binary_search_v2(int *arr, size_t size, int standart)
{
    if (!size)
        return 0;

    size_t begin = 0, end = size;
    size_t step = bit_floor(size);
    if (step != size && compare(arr[step], standart))
    {
        end -= step + 1;
        if (!end)
            return size;

        step = bit_ceil(end);
        begin = size - step;
    }

    for (step /= 2; step != 0; step /= 2)
        if (compare(arr[begin + step], standart))
            begin += step;

    return begin + compare(arr[begin], standart);
}

ssize_t binary_search_rec(int *arr, size_t size, int standart)
{
    if (!size)
        return 0;
    
    size_t median = size / 2;
    if (compare(arr[median], standart))
    {
        ssize_t result = binary_search_rec(arr + median + 1, size - median - 1, standart);
        return median + 1 + result;
    }
    else
        return binary_search_rec(arr, median, standart);
}

size_t bit_floor(size_t size)
{
    return pow(2, size / 2);
}

size_t bit_ceil(size_t size)
{
    return pow(2, size / 2 + 1);
}

int compare(int a, int b)
{
    return a < b;  
}