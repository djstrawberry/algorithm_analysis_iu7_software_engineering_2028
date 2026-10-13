#include "search_algorithms.h"

size_t bit_floor(size_t size);
size_t bit_ceil(size_t size);
int compare(int a, int b);

ssize_t binary_search_branchless(const int *arr, size_t size, int standart)
{
    if (!size)
        return -1;

    size_t begin = 0, end = size;
    size_t step = bit_floor(size);
    if (step != size && compare(arr[step], standart))
    {
        end -= step + 1;
        if (!end)
            return -1;

        step = bit_ceil(end);
        begin = size - step;
    }

    for (step /= 2; step != 0; step /= 2)
        if (compare(arr[begin + step], standart))
            begin += step;

    size_t index = begin + compare(arr[begin], standart);
    return index < size && arr[index] == standart ? (ssize_t)index : -1;
}

search_result_t binary_search_branchless_extra(const int *arr, size_t size, int standart)
{
    search_result_t result = {-1, 0};
    if (!size)
        return result;

    size_t begin = 0, end = size;
    size_t step = bit_floor(size);
    if (step != size)
    {
        result.comparisons++;
        if (compare(arr[step], standart))
        {
            end -= step + 1;
            if (!end)
                return result;

            step = bit_ceil(end);
            begin = size - step;
        }
    }

    for (step /= 2; step != 0; step /= 2)
    {
        result.comparisons++;
        if (compare(arr[begin + step], standart))
            begin += step;
    }

    result.comparisons++;
    size_t index = begin + compare(arr[begin], standart);
    if (index < size)
    {
        result.comparisons++;
        if (arr[index] == standart)
            result.index = (ssize_t)index;
    }
    return result;
}

size_t bit_floor(size_t size)
{
    if (!size)
        return 0;
    size_t power = 1;
    while (power <= size / 2)
        power *= 2;
    return power;
}

size_t bit_ceil(size_t size)
{
    if (size <= 1)
        return 1;
    return bit_floor(size - 1) * 2;
}

int compare(int a, int b)
{
    return a < b;
}
