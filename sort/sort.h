#ifndef SORT_H
#define SORT_H

typedef struct s_array array;

void insertion_sort(array* a, int (*predicate)(const void* lhs, const void* rhs));

#endif
