#ifndef ARRAY_UTILS_H
#define ARRAY_UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

void create_array(int **arr, size_t *size);
void input_array_values(int **arr, size_t size);
int* copy_array(const int *arr, size_t size);
void print_array(const int *arr, size_t size);
void sort_array(int *arr, size_t size);
int* generate_sorted_array(size_t size, int min_value, int max_value);
int* generate_random_array(size_t size, int min_value, int max_value);
bool is_sorted(const int *arr, size_t size);
int find_min(const int *arr, size_t size);
int find_max(const int *arr, size_t size);
bool contains(const int *arr, size_t size, int value);
void free_arr(int *arr);

#endif