#ifndef ARRAY_H
#define ARRAY_H

#include <stdlib.h>

#if __STDC_VERSION__ >= 199901L
    #include <stdbool.h>
#else
    typedef enum { false, true } bool;
#endif


typedef struct s_array
{
    void* data;
    size_t size;
    size_t capacity;
    size_t DATA_SIZE;
}   array;

array* array_create(size_t capacity, size_t data_size);
array* array_filter(const array* src, bool (*filter)(const void*), void (*clone)(void* dst, const void* src));
array* array_copy(const array* src, void (*clone)(void* dst, const void* src));

void array_destroy(array* a, void (*del)(void*));
void array_clear(array* a, void (*del)(void*));
void* array_erase_back(array *a, void (*del)(void*));
void* array_erase_at(array *a, size_t pos, void (*del)(void*));

void* array_push_back(array *a, void* data);
void* array_insert_at(array *a, void* data, size_t pos);

int array_is_empty(const array *a);

void array_sort(array* a, void (*predicate)(void* lhs, void* rhs));

void array_map(array* a, void (*f)(void*));
void* array_at(array *a, size_t pos);

#endif
