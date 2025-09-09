#include "tests.h"

#include "../array.h"

enum greatest_test_res test_array_initialization(void)
{
    array* a = array_create(10, sizeof(int));

    ASSERT_EQ(0, a->size);
    ASSERT_EQ(sizeof(int), a->DATA_SIZE);
    ASSERT_NEQ(NULL, a->data);

    array_destroy(a, NULL);
    PASS();
}