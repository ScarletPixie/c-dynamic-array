#ifndef ARRAY_H
#define ARRAY_H

#include <stdlib.h>

#ifndef __cplusplus
    #if defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L
        #include <stdbool.h>
    #else
        #ifndef __bool_true_false_are_defined
        typedef enum { false = 0, true = 1 } bool;
        #define __bool_true_false_are_defined 1
        #endif
    #endif
#endif


#define DECLARE_ARRAY(TYPE, ALIAS)\
    typedef struct s_array_##ALIAS\
    {\
        TYPE* data;\
        size_t size;\
        size_t capacity;\
    }   array_##ALIAS;\
\
\
    typedef void array_##ALIAS##_del_cb(TYPE);\
    typedef void array_##ALIAS##_map_cb(TYPE*);\
    typedef TYPE array_##ALIAS##_clone_cb(const TYPE);\
    typedef bool array_##ALIAS##_filter_cb(const TYPE);\
\
\
    array_##ALIAS* array_##ALIAS##_create(size_t capacity);\
    array_##ALIAS* array_##ALIAS##_copy(const array_##ALIAS* src, array_##ALIAS##_clone_cb* clone);\
    array_##ALIAS* array_##ALIAS##_filter(\
        const array_##ALIAS* src,\
        array_##ALIAS##_filter_cb* filter,\
        array_##ALIAS##_clone_cb* clone);\
\
    void array_##ALIAS##_delete(array_##ALIAS* a, array_##ALIAS##_del_cb* del);\
\
    void array_##ALIAS##_map(array_##ALIAS* a, array_##ALIAS##_map_cb* cb);\
    TYPE* array_##ALIAS##_at(array_##ALIAS* a, size_t pos);\
    TYPE* array_##ALIAS##_insert_at(array_##ALIAS* a, TYPE data, size_t pos);\
    TYPE* array_##ALIAS##_push_back(array_##ALIAS* a, TYPE data);\

#define DEFINE_ARRAY(TYPE, ALIAS)\
    array_##ALIAS* array_##ALIAS##_filter(\
        const array_##ALIAS* src,\
        array_##ALIAS##_filter_cb* filter,\
        array_##ALIAS##_clone_cb* clone)\
    {\
        if (src == NULL || filter == NULL)\
            return NULL;\
        array_##ALIAS* a = malloc(sizeof(array_##ALIAS));\
        a->size = 0;\
        a->capacity = src->size;\
        a->data = malloc(src->size * sizeof(TYPE));\
        if (a->data == NULL)\
        {\
            free(a);\
            return NULL;\
        }\
        for (size_t i = 0, j = 0; i < src->size; ++i)\
        {\
            if (!filter(src->data[i]))\
                continue;\
            if (clone != NULL)\
                a->data[j] = clone(src->data[i]);\
            else\
                a->data[j] = src->data[i];\
            a->size++;\
            ++j;\
        }\
        return a;\
    }\
    array_##ALIAS* array_##ALIAS##_copy(const array_##ALIAS* src, array_##ALIAS##_clone_cb* clone)\
    {\
        if (src == NULL)\
            return NULL;\
        array_##ALIAS* a = malloc(sizeof(array_##ALIAS));\
        if (a == NULL)\
            return NULL;\
        a->size = src->size;\
        a->capacity = src->capacity;\
        a->data = malloc(src->capacity * sizeof(TYPE));\
        if (a->data == NULL)\
        {\
            free(a);\
            return NULL;\
        }\
        for (size_t i = 0; i < src->size; ++i)\
        {\
            if (clone != NULL)\
                a->data[i] = clone(src->data[i]);\
            else\
                a->data[i] = src->data[i];\
        }\
        return a;\
    }\
    array_##ALIAS* array_##ALIAS##_create(size_t capacity)\
    {\
        array_##ALIAS* a = calloc(1, sizeof(array_##ALIAS));\
        if (a == NULL)\
            return NULL;\
        a->capacity = capacity;\
        a->data = malloc(capacity * sizeof(TYPE));\
        if (a->data == NULL)\
        {\
            free(a);\
            return NULL;\
        }\
        return a;\
    };\
    void array_##ALIAS##_delete(array_##ALIAS* a, array_##ALIAS##_del_cb* del)\
    {\
        if (a == NULL)\
            return;\
\
        if (del != NULL && a->data != NULL)\
        {\
            for (size_t i = 0; i < a->size; ++i)\
                del(a->data[i]);\
        }\
        free(a->data);\
        free(a);\
    };\
\
\
    void array_##ALIAS##_map(array_##ALIAS* a, array_##ALIAS##_map_cb* cb)\
    {\
        if (a == NULL || cb == NULL || a->data == NULL)\
            return;\
        for (size_t i = 0; i < a->size; ++i)\
            cb(&a->data[i]);\
    }\
    TYPE* array_##ALIAS##_at(array_##ALIAS* a, size_t pos)\
    {\
        if (a == NULL || a->data == NULL || pos >= a->size)\
            return NULL;\
        return &a->data[pos];\
    };\
    TYPE* array_##ALIAS##_insert_at(array_##ALIAS* a, TYPE data, size_t pos)\
    {\
        if (a == NULL)\
            return NULL;\
\
        pos = pos > a->size ? a->size : pos;\
        if (a->size >= a->capacity)\
        {\
            const size_t new_cap = ((a->capacity == 0) + a->capacity) * 2;\
            void* tmp = realloc(a->data, new_cap * sizeof(TYPE));\
            if (tmp == NULL)\
                return NULL;\
            a->data = tmp;\
            a->capacity = new_cap;\
        }\
        memmove(\
            &a->data[pos + 1],\
            &a->data[pos],\
            (a->size - pos) * sizeof(TYPE)\
        );\
        a->size++;\
        a->data[pos] = data;\
        return a->data;\
    }\
    TYPE* array_##ALIAS##_push_back(array_##ALIAS* a, TYPE data)\
    {\
        if (a == NULL)\
            return NULL;\
\
        if (a->size >= a->capacity)\
        {\
            const size_t new_cap = ((a->capacity == 0) + a->capacity) * 2;\
            void* tmp = realloc(a->data, new_cap * sizeof(TYPE));\
            if (tmp == NULL)\
                return NULL;\
            a->data = tmp;\
            a->capacity = new_cap;\
        }\
        a->data[a->size] = data;\
        a->size++;\
        return a->data;\
    }\


#endif
