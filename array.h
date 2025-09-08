#ifndef ARRAY_H
#define ARRAY_H

#include <stdlib.h>

typedef struct
{
    void* data;
    size_t size;
    size_t capacity;
    size_t DATA_SIZE;
}   array;

array* array_create(size_t capacity, size_t data_size);
array* array_filter(array* src, int (*filter)(void*), void (*clone)(void* dst, void* src));
array* array_copy(array* src, void (*clone)(void* dst, void* src));

void array_destroy(array* a, void (*del)(void*));
void array_clear(array* a, void (*del)(void*));
void* array_erase_back(array *a, void (*del)(void*));
void* array_erase_at(array *a, size_t pos, void (*del)(void*));

void* array_push_back(array *a, void* data);

int array_is_empty(array *a);

void array_map(array* a, void (*f)(void*));
void* array_at(array *a, size_t pos);

#endif
