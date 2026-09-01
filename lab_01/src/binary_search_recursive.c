#include "search_algorithms.h"

ssize_t binary_search_recursive(const int *arr, size_t size, int standart)
{
    if (!size)
        return 0;
    
    size_t median = size / 2;
    if (compare(arr[median], standart))
    {
        ssize_t result = binary_search_recursive(arr + median + 1, size - median - 1, standart);
        return median + 1 + result;
    }
    else
        return binary_search_recursive(arr, median, standart);
}

search_result_t binary_search_recursive_extra(const int *arr, size_t size, int standart)
{
    search_result_t result = {0, 0, 0};
    
    if (!size)
        return result;
    
    size_t median = size / 2;
    result.comparisons = 1; 
    
    if (compare(arr[median], standart))
    {
        search_result_t sub_result = binary_search_recursive_extra(arr + median + 1, size - median - 1, standart);
        
        result.index = median + 1 + sub_result.index;
        result.comparisons += sub_result.comparisons;
    }
    else
    {
        search_result_t sub_result = binary_search_recursive_extra(arr, median, standart);
        
        result.index = sub_result.index;
        result.comparisons += sub_result.comparisons;
    }
    
    return result;
}