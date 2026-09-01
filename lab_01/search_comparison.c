#define _POSIX_C_SOURCE 199309L  
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

typedef enum
{
    OK_CODE,
    ERR_CODE
} result_t;

long long current_time_ns(void)
{
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return (long long)ts.tv_sec * 1000000000LL + ts.tv_nsec;
}

int main(void)
{
    const size_t ARRAY_SIZE = 100000;   
    const int ITERATIONS = 1000;        

    int *arr = malloc(ARRAY_SIZE * sizeof(int));
    if (!arr)
        return ERR_CODE;

    for (size_t i = 0; i < ARRAY_SIZE; ++i)
        arr[i] = (int)i;

    int target = (int)(ARRAY_SIZE - 1);
    ssize_t pos = -1;
    result_t ec = OK_CODE;

    long long start = current_time_ns();
    for (int i = 0; i < ITERATIONS; ++i)
    {
        ec = binary_search(arr, ARRAY_SIZE, target, &pos);
        if (ec != OK_CODE)
        {
            free(arr);
            return ERR_CODE;
        }
    }
    long long end = current_time_ns();
    double binary_time = (double)(end - start) / ITERATIONS;

    start = current_time_ns();
    for (int i = 0; i < ITERATIONS; ++i)
    {
        ec = linear_search(arr, ARRAY_SIZE, target, &pos);
        if (ec != OK_CODE)
        {
            free(arr);
            return ERR_CODE;
        }
    }
    end = current_time_ns();
    double linear_time = (double)(end - start) / ITERATIONS;

    printf("Размер массива: %zu\n", ARRAY_SIZE);
    printf("Итераций каждого поиска: %d\n", ITERATIONS);
    printf("Искомый элемент: %d (последний)\n\n", target);
    printf("Среднее время бинарного поиска: %.2f нс\n", binary_time);
    printf("Среднее время линейного поиска: %.2f нс\n", linear_time);
    printf("Линейный поиск медленнее бинарного в %.2f раз\n", linear_time / binary_time);
    // printf("%d\n", sizeof(void)); НЕ СКОМПИЛИРУЕТСЯ

    free(arr);
    return OK_CODE;
}

