#include "array_utils.h"
#include <stdint.h>

void create_array(int **arr, size_t *size)
{
    printf("=== ВВОД МАССИВА ===\n");
    printf("Введите размер массива N (0 - использовать массив по умолчанию): ");
    if (scanf("%zu", size) != 1 || *size > SIZE_MAX / sizeof(int)
        || *size > (size_t)PTRDIFF_MAX)
    {
        printf("Некорректный размер массива!\n");
        *arr = NULL;
        return;
    }

    if (!*size)
    {
        static int default_arr[] = {1, 3, 5, 7, 9, 11, 13, 15, 17, 19};
        *size = sizeof(default_arr) / sizeof(default_arr[0]);
        *arr = copy_array(default_arr, *size);
        printf("\nИспользуется массив по умолчанию:\n");
    }
    else
    {
        input_array_values(arr, *size);
        if (*arr)
        {
            printf("\nВведённый массив: ");
            print_array(*arr, *size);
        }
    }


}

void input_array_values(int **arr, size_t size)
{
    *arr = malloc(size * sizeof(int));
    if (!*arr)
    {
        printf("Ошибка выделения памяти!\n");
        return;
    }
    
    printf("Введите %zu элементов массива:\n", size);
    for (size_t i = 0; i < size; i++)
    {
        printf("arr[%zu] = ", i);
        if (scanf("%d", &(*arr)[i]) != 1)
        {
            printf("Некорректный элемент массива!\n");
            free(*arr);
            *arr = NULL;
            return;
        }
    }
}

int* copy_array(const int *arr, size_t size)
{
    int *copy = malloc(size * sizeof(int));
    if (copy)
    {
        for (size_t i = 0; i < size; i++)
            copy[i] = arr[i];
    }
    return copy;
}

void print_array(const int *arr, size_t size)
{
    printf("[");
    for (size_t i = 0; i < size; i++)
    {
        printf("%d", arr[i]);
        if (i + 1 < size)
            printf(", ");
    }
    printf("]\n");
}

void sort_array(int *arr, size_t size)
{
    for (size_t i = 0; i + 1 < size; i++)
    {
        for (size_t j = 0; j < size - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

static void init_random(void)
{
    static bool initialized = false;
    if (!initialized)
    {
        srand(time(NULL));
        initialized = true;
    }
}

int* generate_random_array(size_t size, int min_value, int max_value)
{
    init_random();
    
    int *arr = malloc(size * sizeof(int));
    if (!arr) return NULL;
    
    int range = max_value - min_value + 1;
    for (size_t i = 0; i < size; i++)
        arr[i] = min_value + rand() % range;
    
    return arr;
}

int* generate_sorted_array(size_t size, int min_value, int max_value)
{
    int *arr = generate_random_array(size, min_value, max_value);
    if (arr)
        sort_array(arr, size);
    return arr;
}

bool is_sorted(const int *arr, size_t size)
{
    for (size_t i = 0; i + 1 < size; i++)
    {
        if (arr[i] > arr[i + 1])
            return false;
    }
    return true;
}

int find_min(const int *arr, size_t size)
{
    if (size == 0) return 0;
    
    int min = arr[0];
    for (size_t i = 1; i < size; i++)
    {
        if (arr[i] < min)
            min = arr[i];
    }
    return min;
}

int find_max(const int *arr, size_t size)
{
    if (size == 0) return 0;
    
    int max = arr[0];
    for (size_t i = 1; i < size; i++)
    {
        if (arr[i] > max)
            max = arr[i];
    }
    return max;
}

bool contains(const int *arr, size_t size, int value)
{
    for (size_t i = 0; i < size; i++)
    {
        if (arr[i] == value)
            return true;
    }
    return false;
}

void free_arr(int *arr)
{
    if (arr)
    {
        free(arr);
        arr = NULL;
    }
}