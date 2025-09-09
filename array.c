#include "array.h"

#include <string.h>

int array_is_empty(const array *a)
{
    return a == NULL || a->size == 0 || a->data == NULL;
}


array* array_create(size_t capacity, size_t data_size)
{
    array* const a = malloc(sizeof(*a));
    if (a == NULL)
        return NULL;

    a->capacity = capacity;
    a->size = 0;
    a->DATA_SIZE = data_size;
    a->data = malloc(capacity * data_size);
    if (a->data == NULL && capacity != 0)
    {
        free(a);
        return NULL;
    }
    return a;
}

array* array_filter(const array* src, int (*filter)(const void*), void (*clone)(void*, const void*))
{
    if (array_is_empty(src) || filter == NULL)
        return NULL;

    array* const a = array_create(src->size, src->DATA_SIZE);
    if (a == NULL)
        return NULL;

    unsigned char* start = src->data;
    for (size_t i = 0; i < (src->size * src->DATA_SIZE); i += src->DATA_SIZE)
    {
        if (!filter(start + i))
            continue;
        if (clone != NULL)
            clone(a->data + i, src->data + i);
        else
            memcpy(a->data + i, src->data + i, src->DATA_SIZE);
        a->size++;
    }

    return a;
}

array* array_copy(const array* src, void (*clone)(void* dst, const void* src))
{
    if (array_is_empty(src))
        return NULL;

    array* const a = array_create(src->capacity, src->DATA_SIZE);
    if (a == NULL)
        return NULL;
    a->size = src->size;

    unsigned char* start = src->data;
    for (size_t i = 0; i < (src->size * src->DATA_SIZE); i += src->DATA_SIZE)
    {
        if (clone != NULL)
            clone(a->data + i, src->data + i);
        else
            memcpy(a->data + i, src->data + i, src->DATA_SIZE);
    }

    return a;
}


void* array_at(array *a, size_t pos)
{
    if (array_is_empty(a) || pos >= a->size)
        return NULL;

    unsigned char* start = a->data;
    return start + (pos * a->DATA_SIZE);
}
void* array_push_back(array* a, void* data)
{
    if (a == NULL || data == NULL)
        return NULL;

    if (a->size >= a->capacity)
    {
        const size_t new_cap = ((a->capacity == 0) + a->capacity) * 2;
        void* tmp = realloc(a->data, new_cap * a->DATA_SIZE);
        if (tmp == NULL)
            return NULL;
        a->data = tmp;
        a->capacity = new_cap;
    }
    unsigned char* start = a->data;
    memcpy(start + (a->size * a->DATA_SIZE), data, a->DATA_SIZE);
    a->size++;
    return a->data;
}
void* array_erase_back(array *a, void (*del)(void*))
{
    if (a == NULL || a->data == NULL || a->size == 0)
        return NULL;

    unsigned char* start = a->data;
    unsigned char* target = start + ((a->size - 1) * a->DATA_SIZE);

    if (del != NULL)
        del(target);
    a->size--;
    return a->data;
}
void* array_erase_at(array *a, size_t pos, void (*del)(void*))
{
    if (a == NULL || pos >= a->size || a->size == 0)
        return NULL;

    unsigned char* start = a->data;
    unsigned char* target = start + (pos * a->DATA_SIZE);

    if (del != NULL)
        del(target);
    a->size--;
    if (pos != a->size - 1)
        memmove(target, target + a->DATA_SIZE, (a->size - pos) * a->DATA_SIZE);
    return a->data;
}
void array_destroy(array* a, void (*del)(void*))
{
    if (a == NULL)
        return;

    if (del != NULL)
    {
        unsigned char* start = a->data;
        const size_t target_size = a->size * a->DATA_SIZE;
        for (size_t i = 0; i < target_size; i += a->DATA_SIZE)
            del(start + i);
    }

    free(a->data);
    free(a);
}
void array_clear(array* a, void (*del)(void*))
{
    if (a == NULL)
        return;

    unsigned char* start = a->data;
    const size_t target_size = a->size * a->DATA_SIZE;
    for (size_t i = 0; i < target_size; i += a->DATA_SIZE)
    {
        if (del != NULL)
            del(start + i);
    }
    a->size = 0;
}


void array_map(array* a, void (*f)(void*))
{
    if (a == NULL || a->data == NULL || f == NULL)
        return;

    unsigned char* start = a->data;
    const size_t target_size = a->size * a->DATA_SIZE;
    for (size_t i = 0; i < target_size; i += a->DATA_SIZE)
        f(start + i);
}
