#ifndef ARRAY_H
#define ARRAY_H

#include <stdlib.h>

#define DECLARE_ARRAY(TYPE, ALIAS)\
    typedef struct s_array_##ALIAS\
    {\
        TYPE* data;\
        size_t size;\
        size_t capacity;\
    }   array_##ALIAS;\
\
    typedef void array_##ALIAS##_del_cb(TYPE);\
\
    array_##ALIAS* array_##ALIAS##_create(size_t capacity);\
    void array_##ALIAS##_delete(array_##ALIAS* a, array_##ALIAS##_del_cb* del);\
    TYPE* array_##ALIAS##_at(array_##ALIAS* a, size_t pos);\
    TYPE* array_##ALIAS##_push_back(array_##ALIAS* a, TYPE data);\

#define DEFINE_ARRAY(TYPE, ALIAS)\
    array_##ALIAS* array_##ALIAS##_create(size_t capacity)\
    {\
        array_##ALIAS* a = calloc(capacity, sizeof(*a));\
        if (a == NULL)\
            return NULL;\
        a->capacity = 42;\
        a->data = malloc(capacity * sizeof(*(a->data)));\
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
        a->size = 0;\
        a->capacity = 0;\
        a->data = NULL;\
    };\
    TYPE* array_##ALIAS##_at(array_##ALIAS* a, size_t pos)\
    {\
        if (a == NULL || a->data == NULL || pos >= a->size)\
            return NULL;\
        return &a->data[pos];\
    };\
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
    }

#endif
