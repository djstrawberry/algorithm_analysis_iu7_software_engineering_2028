#include <assert.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include "search_algorithms.h"

static size_t checks;
static void check(const int *a, size_t n, int x)
{
    search_func plain[] = {linear_search, binary_search_classic,
        binary_search_branchless, binary_search_recursive};
    search_result_t (*extra[])(const int *, size_t, int) = {
        linear_search_extra, binary_search_classic_extra,
        binary_search_branchless_extra, binary_search_recursive_extra};
    ssize_t expected = linear_search(a, n, x);
    for (size_t j = 0; j < 4; j++)
    {
        ssize_t p = plain[j](a, n, x);
        search_result_t r = extra[j](a, n, x);
        assert(p == r.index);
        assert((p == -1) == (expected == -1));
        assert(p == -1 || ((size_t)p < n && a[p] == x));
        if (!n) assert(r.comparisons == 0);
        checks++;
    }
}

int main(void)
{
    check(NULL, 0, 7);
    int single[] = {4};
    check(single, 1, 4);
    check(single, 1, 3);
    check(single, 1, 5);
    int five[] = {0, 2, 4, 6, 8};
    check(five, 5, 0);
    check(five, 5, 4);
    check(five, 5, 8);
    check(five, 5, 3);
    int duplicates[] = {1, 1, 1, 2};
    check(duplicates, 4, 1);
    int extremes[] = {INT_MIN, 0, INT_MAX};
    check(extremes, 3, INT_MIN);
    check(extremes, 3, INT_MAX);
    check(extremes, 3, -1);
    for (size_t n = 1; n <= 256; n++)
    {
        int *a = malloc(n * sizeof(*a));
        assert(a);
        for (size_t i = 0; i < n; i++) a[i] = 2 * (int)i;
        for (int x = -1; x <= 2 * (int)n; x++) check(a, n, x);
        for (size_t i = 0; i < n; i++) a[i] = (int)(i / 3);
        for (int x = -1; x <= (int)n / 3 + 1; x++) check(a, n, x);
        free(a);
    }
    int a[] = {0, 2, 4, 6, 8, 10, 12, 14};
    assert(linear_search_extra(a, 8, 0).comparisons == 1);
    assert(linear_search_extra(a, 8, -1).comparisons == 8);
    assert(binary_search_classic_extra(a, 8, 8).comparisons == 2);
    assert(binary_search_classic_extra(a, 8, -1).comparisons == 8);
    assert(binary_search_recursive_extra(a, 8, 8).comparisons == 1);
    assert(binary_search_recursive_extra(a, 8, -1).comparisons == 8);
    for (int x = -1; x <= 16; x++)
        assert(binary_search_branchless_extra(a, 8, x).comparisons ==
               (size_t)(x > 14 ? 4 : 5));
    printf("Validated algorithm results: %zu\n", checks);
    puts("Comparison-counter checks: passed");
    return 0;
}
