#include "dispatcher.h"

void dispatch_menu_choice(int choice, int *arr, const int *sorted, size_t size)
{
    switch(choice)
    {
        case 1:
            run_search_menu(arr, sorted, size);
            break;
            
        case 2:
            run_benchmark(arr, sorted, size);
            break;
            
        case 0:
            break;
            
        default:
            printf("Оп, мисклик!\n");
    }
}