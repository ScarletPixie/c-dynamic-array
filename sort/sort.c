#include "sort.h"

#include "../array.h"

static void memswap(void* lhs, void* rhs, size_t size);

void insertion_sort(array* a, int (*predicate)(const void* lhs, const void* rhs))
{
    if (array_is_empty(a) || predicate == NULL)
        return;
   
    unsigned char* start = a->data;
    for (size_t i = 0; i < (a->size * a->DATA_SIZE); i += a->DATA_SIZE)
    {
        void* lhs = start + i;
        for (size_t j = i + a->DATA_SIZE;  j < (a->size * a->DATA_SIZE); j += a->DATA_SIZE)
        {
            void* rhs = start + j;

            // IF predicate says LHS is BIGGER than RHS swap.
            if (predicate(lhs, rhs) > 0)
                memswap(lhs, rhs, a->DATA_SIZE);
        }
    }
}

static void memswap(void* l, void* r, size_t size)
{
    unsigned char* lhs = l;
    unsigned char* rhs = r;
    unsigned char buffer;

    for (size_t byte = 0; byte < size; ++byte)
    {
        buffer = lhs[byte];
        lhs[byte] = rhs[byte];
        rhs[byte] = buffer;
    }
}
