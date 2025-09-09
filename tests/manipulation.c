#include "tests.h"

#include "../array.h"

enum greatest_test_res test_array_insertion(void)
{
    int data = 42;
    array* a = array_create(0, sizeof(int));

    array_push_back(a, &data);
    ASSERT_EQ(1, a->size);
    ASSERT_NEQ(NULL, array_at(a, 0));
    ASSERT_EQ(42, *(int*)array_at(a, 0));

    array_destroy(a, NULL);
    PASS();
}