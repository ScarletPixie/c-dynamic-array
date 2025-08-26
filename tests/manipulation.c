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
enum greatest_test_res test_array_insert_at(void)
{
    size_t data = 42;
    array* a = array_create(0, sizeof(size_t));
    for (size_t i = 0; i < 13; ++i)
        array_push_back(a, &i);
    array_insert_at(a, &data, 0);
    ASSERT_EQ(42, array_at(a, 0));
    array_insert_at(a, &data, 5);
    ASSERT_EQ(42, array_at(a, 5));
    PASS();
}
