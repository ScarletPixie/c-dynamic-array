#include "tests.h"
#include "greatest.h"

#include <string.h>


static bool is_odd(int n);
static char* my_strdup(const char* s);
static void str_free(char* s);

DECLARE_ARRAY(int, int); DEFINE_ARRAY(int, int);
DECLARE_ARRAY(char*, str); DEFINE_ARRAY(char*, str);

TEST test_array_create(void);
TEST test_array_copy(void);
TEST test_array_filter(void);

TEST test_array_insertion(void);
TEST test_array_access(void);

SUITE(test_array_creation)
{
    RUN_TEST(test_array_create);
    RUN_TEST(test_array_copy);
    RUN_TEST(test_array_filter);
}
SUITE(test_array_modification)
{
    RUN_TEST(test_array_access);
    RUN_TEST(test_array_insertion);
}


TEST test_array_filter(void)
{
    array_int* a = array_int_create(100);
    for (size_t i = 0; i < 10; ++i)
        array_int_insert_at(a, i, i);

    array_int* b = array_int_filter(a, is_odd, NULL);
    ASSERT_NEQ(NULL, b);
    ASSERT_NEQ(NULL, b->data);
    ASSERT_EQ(5, b->size);
    for (size_t i = 0, odd_num = 1; i < 5; ++i, odd_num += 2)
        ASSERT_EQ_FMT(odd_num, (size_t)*array_int_at(b, i), "%zu");

    array_int_delete(a, NULL);
    array_int_delete(b, NULL);
    PASS();
}
TEST test_array_copy(void)
{
    array_str* a = array_str_create(100);
    for (size_t i = 0; i < 10; ++i)
        array_str_push_back(a, my_strdup("potato"));

    array_str* b = array_str_copy(a, my_strdup);
    for (size_t i = 0; i < 10; ++i)
        ASSERT_STR_EQ(*array_str_at(a, 0), *array_str_at(b, 0));

    char* a_first_word = *array_str_at(a, 0);
    a_first_word[0] = 'b';

    ASSERT_STR_EQ(*array_str_at(a, 0), "botato");
    ASSERT_NEQ(strcmp(*array_str_at(a, 0), *array_str_at(b, 0)), 0);

    array_str_delete(a, str_free);
    array_str_delete(b, str_free);
    PASS();
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
    array_int_delete(a, NULL);
    PASS();
}

TEST test_array_create(void)
{
    array_int* a = array_int_create(42);
    ASSERT_NEQ(NULL, a->data);
    ASSERT_EQ(42, a->capacity);
    ASSERT_EQ(0, a->size);
    array_int_delete(a, NULL);
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

    array_int_delete(a, NULL);
    PASS();
}
static char* my_strdup(const char* s)
{
    size_t size = strlen(s);
    char* res = malloc((size + 1) * sizeof(*res));
    memcpy(res, s, size * sizeof(*res));
    res[size] = '\0';
    return res;
}
static void str_free(char* s) { free(s); }
static bool is_odd(int n) { return n % 2; }