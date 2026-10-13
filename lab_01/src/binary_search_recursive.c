#include "search_algorithms.h"

static int compare(int a, int b);

ssize_t binary_search_recursive(const int *arr, size_t size, int standart)
{
    if (!size)
        return -1;

    size_t median = size / 2;

    if (arr[median] == standart)
        return (ssize_t)median;

    if (compare(arr[median], standart))
    {
        ssize_t result = binary_search_recursive(arr + median + 1, size - median - 1, standart);
        if (result == -1)
            return -1;
        return (ssize_t)(median + 1) + result;
    }

    return binary_search_recursive(arr, median, standart);
}

search_result_t binary_search_recursive_extra(const int *arr, size_t size, int standart)
{
    search_result_t result = {-1, 0};

    if (!size)
        return result;

    size_t median = size / 2;
    result.comparisons = 1;

    if (arr[median] == standart)
    {
        result.index = (ssize_t)median;
        return result;
    }

    result.comparisons++;
    search_result_t sub;

    if (compare(arr[median], standart))
    {
        sub = binary_search_recursive_extra(arr + median + 1, size - median - 1, standart);
        if (sub.index == -1)
            result.index = -1;
        else
            result.index = (ssize_t)(median + 1) + sub.index;
    }
    else
    {
        sub = binary_search_recursive_extra(arr, median, standart);
        result.index = sub.index;
    }

    result.comparisons += sub.comparisons;
    return result;
}

static int compare(int a, int b)
{
    return a < b;
}
