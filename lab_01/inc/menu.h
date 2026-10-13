#ifndef MENU_H
#define MENU_H

#include <stdio.h>
#include <stdlib.h>
#include "search_algorithms.h"

void print_main_menu(void);
void run_array_creation_menu(int **arr, size_t *size);
void run_search_menu(int *arr, const int *sorted, size_t size);
void run_benchmark(const int *arr, const int *sorted, size_t size);

#endif