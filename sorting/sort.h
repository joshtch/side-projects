#ifndef SORT_H
#define SORT_H
#include <stdio.h>

/* Usage is exactly the same as the qsort function in stdlib.h */
void sort(void* arr, size_t num, size_t size,
            int (*cmp)(const void*, const void*));

#endif
