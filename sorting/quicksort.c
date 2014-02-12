#include "quicksort.h"

typedef size_t Index;
typedef void* Value;
#define CMP_PROTOTYPE(NAME) int (*NAME)(const void*, const void*)

static void private_qsort(void* arr, size_t size, CMP_PROTOTYPE(cmp),
            Index left, Index right, Index pivot);
static Index choose_pivot(void* arr, size_t length, size_t size,
            CMP_PROTOTYPE(cmp));

void qsort(void* arr, size_t length, size_t size, CMP_PROTOTYPE(cmp))
{
    if (length > 1) {
        Index pivot = choose_pivot(arr, length, size, cmp);
        return private_qsort(arr, size, cmp, 0, length - 1, pivot);
    }
}

/* ------------------------------ Sorting ---------------------------------- */

static void swap(void* arr, size_t size, Index first, Index second);

static void private_qsort(void* arr, size_t size, CMP_PROTOTYPE(cmp),
            Index left, Index right, Index pivot)
{
}

static void segment_reorder(void* arr, size_t size, CMP_PROTOTYPE(cmp),
        Index left, Index right, Index pivot)
{
#define VALUE(INDEX) ((char*)(arr) + (INDEX)*(size))
    Index i = left;
    Index j = right;
    Value pivot_val = VALUE(pivot);
    int j_vs_pivot;
    Value i_val, j_val;

    i = iterate_left_marker(arr, size, cmp, i, pivot_val, j);
    while (i < j) {
        i = iterate_left_marker(arr, size, cmp, i, pivot_val, j);
        i_val = VALUE(i);
        if (cmp(i_val, pivot_val) >= 0) {
            j_vs_pivot = cmp(VALUE(j), pivot_val);
            while (j_vs_pivot >= 0) {
                --j;
                j_vs_pivot = cmp(VALUE(j), pivot_val);
            }
            if (i_val != VALUE(j))
                swap(arr, size, i, j);
        }
        ++i;
    }
}

static Index iterate_left_marker(void* arr, size_t size, CMP_PROTOTYPE(cmp),
        Index left, Value pivot_val, Index limit)
{
#define VALUE(INDEX) ((char*)(arr) + (INDEX)*(size))
    while (left < limit && cmp(VALUE(left), pivot_val) < 0)
        ++left;
    return left;
}

static void swap(void* arr, size_t size, Index first, Index second)
{
    char* iter = arr;
    int i;
    for (i = 0; i < size; ++i) {
        iter[first*size + i]  ^= iter[second*size + i];
        iter[second*size + i] ^= iter[first*size + i];
        iter[first*size + i]  ^= iter[second*size + i];
    }
}


/* ----------------------------- Pivot choosing ---------------------------- */

static Index lesser_of(void* arr, size_t size, CMP_PROTOTYPE(cmp), Index first,
            Index second);
static Index greater_of(void* arr, size_t size, CMP_PROTOTYPE(cmp), Index first,
            Index second);

/* Returns index of median of the left, right, and middle values of the array */
static Index choose_pivot(void* arr, size_t length, size_t size,
        CMP_PROTOTYPE(cmp))
{
    if (lesser_of(arr, size, cmp, 0, length - 1) == 0)
        return (greater_of(arr, size, cmp, 0, length/2));
    else
        return (greater_of(arr, size, cmp, length/2, length));
}

/*
 * The following two functions could be combined into a single macro, but this
 * method is more readable and much safer
 */

static Index lesser_of(void* arr, size_t size, CMP_PROTOTYPE(cmp), Index first,
        Index second)
{
    char* a = arr;
    void* first_byte_index  = a + first*size;
    void* second_byte_index = a + second*size;
    if (cmp(first_byte_index, second_byte_index) < 0)
        return first;
    else
        return second;
}
static Index greater_of(void* arr, size_t size, CMP_PROTOTYPE(cmp), Index first,
            Index second)
{
    char* a = arr;
    void* first_byte_index  = a + first*size;
    void* second_byte_index = a + second*size;
    if (cmp(first_byte_index, second_byte_index) > 0)
        return first;
    else
        return second;
}

#undef CMP_PROTOTYPE
