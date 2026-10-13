#include <stdio.h>
#include "menu.h"
#include "array_utils.h"
#include "dispatcher.h"

int main(void)
{
    int *arr = NULL;
    size_t size = 0;
    int choice = 0;
    create_array(&arr, &size);
    if (!arr)
        return EXIT_FAILURE;
    int *sorted = copy_array(arr, size);
    if (!sorted)
    {
        free_arr(arr);
        return EXIT_FAILURE;
    }
    sort_array(sorted, size);
    printf("Исходный массив: ");
    print_array(arr, size);
    printf("Отсортированная копия: ");
    print_array(sorted, size);
    do
    {
        print_main_menu();
        if (scanf("%d", &choice) != 1)
            break;
        dispatch_menu_choice(choice, arr, sorted, size);
    } while (choice);
    free_arr(sorted);
    free_arr(arr);
    return 0;
}
