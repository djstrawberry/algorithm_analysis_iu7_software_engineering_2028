#include <stdio.h>
#include <stdlib.h>
#include "search_algorithms.h"

int main(void)
{
    size_t sizes[] = {1, 2, 3, 8, 10, 16, 32, 64, 128, 256, 1024};
    puts("N,linear_min,linear_max,classic_min,classic_max,branchless_min,branchless_max,recursive_min,recursive_max");
    for (size_t s = 0; s < sizeof(sizes) / sizeof(sizes[0]); s++)
    {
        size_t n = sizes[s];
        int *a = malloc(n * sizeof(*a));
        if (!a) return EXIT_FAILURE;
        for (size_t i = 0; i < n; i++) a[i] = 2 * (int)i;
        size_t lo[4] = {n * 2 + 1, n * 2 + 1, n * 2 + 1, n * 2 + 1};
        size_t hi[4] = {0};
        for (int x = -1; x <= 2 * (int)n; x++)
        {
            search_result_t r[] = {linear_search_extra(a,n,x),
                binary_search_classic_extra(a,n,x),
                binary_search_branchless_extra(a,n,x),
                binary_search_recursive_extra(a,n,x)};
            for (size_t j = 0; j < 4; j++)
            {
                if (r[j].comparisons < lo[j]) lo[j] = r[j].comparisons;
                if (r[j].comparisons > hi[j]) hi[j] = r[j].comparisons;
            }
        }
        printf("%zu", n);
        for (size_t j = 0; j < 4; j++) printf(",%zu,%zu", lo[j], hi[j]);
        putchar('\n');
        free(a);
    }
    return 0;
}
