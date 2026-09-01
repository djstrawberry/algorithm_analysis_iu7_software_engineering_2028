#ifndef SEARCH_ALGORITHMS_H
#define SEARCH_ALGORITHMS_H

#include <unistd.h>
#include <math.h>

typedef struct {
    ssize_t index;          
    size_t comparisons;      
} search_result_t;

ssize_t linear_search(const int *arr, size_t size, int standart);
ssize_t binary_search_classic(const int *arr, size_t size, int standart);
ssize_t binary_search_branchless(const int *arr, size_t size, int standart);
ssize_t binary_search_recursive(const int *arr, size_t size, int standart);

search_result_t linear_search_extra(const int *arr, size_t size, int standart);
search_result_t binary_search_classic_extra(const int *arr, size_t size, int standart);
search_result_t binary_search_branchless_extra(const int *arr, size_t size, int standart);
search_result_t binary_search_recursive_extra(const int *arr, size_t size, int standart);

#endif