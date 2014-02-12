#include "quicksort.h"

typedef size_t Index;
typedef void* Value;
#define CMP_PROTOTYPE(NAME) int (*NAME)(const void*, const void*)

static void private_qsort(void* arr, size_t size, CMP_PROTOTYPE(cmp),
            Index left, Index right);
static Index choose_pivot(void* arr, size_t size, Index left, Index right,
            CMP_PROTOTYPE(cmp));

void qsort(void* arr, size_t length, size_t size, CMP_PROTOTYPE(cmp))
{
    if (length > 1) {
        return private_qsort(arr, size, cmp, 0, length - 1);
    }
}


/* ------------------------------ Sorting ---------------------------------- */

static void swap(void* arr, size_t size, Index first, Index second);

static Index iterate_left_marker(void* arr, size_t size, CMP_PROTOTYPE(cmp),
        Index left, Value pivot_val, Index limit);
static Index iterate_right_marker(void* arr, size_t size, CMP_PROTOTYPE(cmp),
        Index right, Value pivot_val, Index limit);

static void private_qsort(void* arr, size_t size, CMP_PROTOTYPE(cmp),
        Index left, Index right)
{
#define VALUE(INDEX) ((char*)(arr) + (INDEX)*(size))
    Index i = left;
    Index j = right;
    Index k, left_of_pivot_max, right_of_pivot_min;
    int comparison;
    Index pivot = choose_pivot(arr, size, left, right, cmp);
    Value pivot_val = VALUE(pivot);

    i = iterate_left_marker(arr, size, cmp, i, pivot_val, j);
    j = iterate_right_marker(arr, size, cmp, j, pivot_val, i);
    k = i;
    while (i < j) {
        left_of_pivot_max = i;
        right_of_pivot_min = j;
        while ((comparison = cmp(VALUE(k), pivot_val)) == 0 && k != j) {
            ++k;
        }
        if (k == j) break;
        if (comparison < 0) {
            swap(arr, size, k, i);
            i = iterate_left_marker(arr, size, cmp, i, pivot_val, j);
        } else if (comparison > 0) {
            swap(arr, size, k, j);
            j = iterate_right_marker(arr, size, cmp, j, pivot_val, i);
        }
    }
    private_qsort(arr, size, cmp, left, left_of_pivot_max);
    private_qsort(arr, size, cmp, right, right_of_pivot_min);
}

static Index iterate_left_marker(void* arr, size_t size, CMP_PROTOTYPE(cmp),
        Index left, Value pivot_val, Index limit)
{
#define VALUE(INDEX) ((char*)(arr) + (INDEX)*(size))
    while (left <= limit && cmp(VALUE(left), pivot_val) < 0)
        ++left;
    return left;
}

static Index iterate_right_marker(void* arr, size_t size, CMP_PROTOTYPE(cmp),
        Index right, Value pivot_val, Index limit)
{
#define VALUE(INDEX) ((char*)(arr) + (INDEX)*(size))
    while (right >= limit && cmp(VALUE(right), pivot_val) > 0)
        --right;
    return right;
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
static Index choose_pivot(void* arr, size_t size, Index left, Index right,
        CMP_PROTOTYPE(cmp))
{
    if (lesser_of(arr, size, cmp, left, right) == 0)
        return (greater_of(arr, size, cmp, left, left + (right - left) / 2));
    else
        return (greater_of(arr, size, cmp, left + (right - left) / 2, right));
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
