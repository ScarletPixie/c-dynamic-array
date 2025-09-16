#include "tests.h"
#include "greatest.h"

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

TEST test_array_insertion(void)
{
    array_int* a = array_int_create(0);
    for (int i = 0; i < 10; ++i)
        array_int_push_back(a, i);
    
    for (int i = 0; i < 10; ++i)
        ASSERT_EQ(i, *array_int_at(a, i));
    PASS();
}

SUITE(test_array_creation)
{
    RUN_TEST(test_array_create);
    RUN_TEST(test_array_insertion);
}
