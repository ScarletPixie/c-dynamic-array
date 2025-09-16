#include "tests.h"
#include "greatest.h"

DECLARE_ARRAY(int, int); DEFINE_ARRAY(int, int);
DECLARE_ARRAY(char*, str); DEFINE_ARRAY(char*, str);

TEST test_array_create(void);
TEST test_array_insertion(void);
TEST test_array_access(void);

SUITE(test_array_creation)
{
    RUN_TEST(test_array_create);
    RUN_TEST(test_array_access);
    RUN_TEST(test_array_insertion);
}

TEST test_array_access(void)
{
    array_int* a = array_int_create(0);
    ASSERT_EQ(NULL, array_int_at(a, 0));
    ASSERT_EQ(NULL, array_int_at(a, 1));

    array_int_push_back(a, 42);
    ASSERT_EQ(42, *array_int_at(a, 0));
    *array_int_at(a, 0) = 21;
    ASSERT_EQ(21, *array_int_at(a, 0));
    PASS();
}

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

    array_int_insert_at(a, 42, 5);
    for (int i = 0; i < 5; ++i)
        ASSERT_EQ(i, *array_int_at(a, i));
    ASSERT_EQ(42, *array_int_at(a, 5));
    for (int i = 6; i < (int)a->size; ++i)
        ASSERT_EQ_FMT(i - 1, *array_int_at(a, i), "%d");

    array_int_insert_at(a, -1, 0);
    array_int_insert_at(a, -2, 999);

    ASSERT_EQ(-1, *array_int_at(a, 0));
    ASSERT_EQ(-2, *array_int_at(a, a->size - 1));
    for (int i = 1; i < 6; ++i)
        ASSERT_EQ(i - 1, *array_int_at(a, i));
    ASSERT_EQ(42, *array_int_at(a, 6));
    for (int i = 7; i < (int)(a->size - 1); ++i)
        ASSERT_EQ_FMT(i - 2, *array_int_at(a, i), "%d");

    PASS();
}