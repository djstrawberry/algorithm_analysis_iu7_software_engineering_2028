#ifndef SEARCH_ALGORITHMS_H
#define SEARCH_ALGORITHMS_H

#include <unistd.h>
#include <math.h>

#define NUM_ALGORITHMS (sizeof(algorithms) / sizeof(algorithms[0]))

typedef struct {
    ssize_t index;          
    size_t comparisons;      
} search_result_t;

typedef ssize_t (*search_func)(const int *arr, size_t size, int standart);

typedef struct {
    const char *name;
    search_func func;
} search_algorithm_t;

ssize_t linear_search(const int *arr, size_t size, int standart);
ssize_t binary_search_classic(const int *arr, size_t size, int standart);
ssize_t binary_search_branchless(const int *arr, size_t size, int standart);
ssize_t binary_search_recursive(const int *arr, size_t size, int standart);

search_result_t linear_search_extra(const int *arr, size_t size, int standart);
search_result_t binary_search_classic_extra(const int *arr, size_t size, int standart);
search_result_t binary_search_branchless_extra(const int *arr, size_t size, int standart);
search_result_t binary_search_recursive_extra(const int *arr, size_t size, int standart);

static const search_algorithm_t algorithms[] = {
    {"Линейный поиск", linear_search},
    {"Бинарный поиск (стандартный)", binary_search_classic},
    {"Бинарный поиск (branchless)", binary_search_branchless},
    {"Бинарный поиск (рекурсивный)", binary_search_recursive}
};

#endif