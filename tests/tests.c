#include "tests.h"
#include "greatest.h"

#include <stdio.h>
#include <string.h>

DECLARE_ARRAY(int, int); DEFINE_ARRAY(int, int);
DECLARE_ARRAY(char*, str); DEFINE_ARRAY(char*, str);

TEST test_array_create(void)
{
    array_int* a = array_int_create(42);
    ASSERT_NEQ(NULL, a->data);
    ASSERT_EQ(42, a->capacity);
    ASSERT_EQ(0, a->size);
    PASS();
}

SUITE(test_array_creation)
{
    RUN_TEST(test_array_create);
}