#include "menu.h"

void print_main_menu(void)
{
    printf("\n=== ГЛАВНОЕ МЕНЮ ===\n");
    printf("1. Поиск элемента\n");
    printf("2. Сравнительный бенчмарк\n");
    printf("0. Выход\n");
    printf("Ваш выбор: ");
}

void run_search_menu(int *arr, const int *sorted, size_t size)
{
    int target;
    printf("Введите значение для поиска: ");
    if (scanf("%d", &target) != 1)
        return;
    
    int choice;
    do
    {
        printf("\n=== ВЫБОР АЛГОРИТМА ПОИСКА ===\n");
        for (size_t i = 0; i < NUM_ALGORITHMS; i++)
            printf("%zu. %s\n", i + 1, algorithms[i].name);
        printf("0. Назад\n");
        printf("Ваш выбор: ");
        if (scanf("%d", &choice) != 1)
            return;
        
        if (choice == 0)
            return;
        
        if (choice < 1 || choice > (int)NUM_ALGORITHMS)
        {
            printf("Оп, мисклик!\n");
            continue;
        }
        
        size_t idx = choice - 1;
        ssize_t result = algorithms[idx].func(idx == 0 ? arr : sorted, size, target);
        
        printf("\n--- %s ---\n", algorithms[idx].name);
        printf("Индекс относится к %s массиву.\n", idx == 0 ? "исходному" : "отсортированному");
        if (result != -1)
            printf("Элемент %d найден на индексе %ld\n", target, result);
        else
            printf("Элемент %d не найден\n", target);
        
    } while (choice);
}

void run_benchmark(const int *arr, const int *sorted, size_t size)
{
    int target;
    printf("Введите значение для поиска: ");
    if (scanf("%d", &target) != 1)
        return;
    
    printf("Индекс линейного поиска относится к исходному массиву,\n");
    printf("индексы бинарных поисков — к отсортированной копии.\n");
    printf("\n┌─────────────────────────────────────────────────────┐\n");
    printf("│ БЕНЧМАРК: N = %-5zu x = %-5d                       │\n", size, target);
    printf("├────────────────────────────┬───────────┬────────────┤\n");
    printf("│ Алгоритм                   │ Индекс    │ Сравнений  │\n");
    printf("├────────────────────────────┼───────────┼────────────┤\n");
    
    search_result_t results[4];
    results[0] = linear_search_extra(arr, size, target);
    results[1] = binary_search_classic_extra(sorted, size, target);
    results[2] = binary_search_branchless_extra(sorted, size, target);
    results[3] = binary_search_recursive_extra(sorted, size, target);
    
    const char *names[] = {
        "Линейный поиск            ",
        "Бинарный стандартный      ",
        "Бинарный branchless       ",
        "Бинарный рекурсивный      "
    };
    
    for (int i = 0; i < 4; i++)
    {
        printf("│ %s │ %-9ld │ %-10zu │\n", 
               names[i], results[i].index, results[i].comparisons);
    }
    
    printf("└────────────────────────────┴───────────┴────────────┘\n");
}