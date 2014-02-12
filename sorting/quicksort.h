#ifndef QUICKSORT_H
#define QUICKSORT_H
#include <stdio.h>

/* Usage is exactly the same as the qsort function in stdlib.h */
void qsort(void* arr, size_t num, size_t size,
            int (*cmp)(const void*, const void*));

#endif
