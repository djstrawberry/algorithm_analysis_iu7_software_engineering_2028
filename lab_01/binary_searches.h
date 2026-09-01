#ifndef BINARY_SEARCHES_H
#define BINARY_SEARCHES_H

#include <unistd.h>
#include <math.h>

ssize_t binary_search_v1(int *arr, size_t size, int standart);
ssize_t binary_search_v2(int *arr, size_t size, int standart);
ssize_t binary_search_rec(int *arr, size_t size, int standart);

#endif