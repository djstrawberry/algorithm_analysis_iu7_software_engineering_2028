#include "search_algorithms.h"

size_t bit_floor(size_t size);
size_t bit_ceil(size_t size);
int compare(int a, int b);

ssize_t binary_search_branchless(const int *arr, size_t size, int standart)
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

search_result_t binary_search_branchless_extra(const int *arr, size_t size, int standart)
{
    search_result_t result = {-1, 0 , 0};
    if (!size)
        return result;

    size_t begin = 0, end = size;
    size_t step = bit_floor(size);
    if (step != size && compare(arr[step], standart))
    {
        result.comparisons++;
        end -= step + 1;
        if (!end)
            return result;

        step = bit_ceil(end);
        begin = size - step;
    }

    for (step /= 2; step != 0; step /= 2)
    {
        result.comparisons++;
        if (compare(arr[begin + step], standart))
            begin += step;
    }

    result.comparisons++;
    result.index = begin + compare(arr[begin], standart);

    return result;
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