#include "tests.h"
#include "greatest.h"

#include <stdio.h>
#include <string.h>

static char* my_strdup(const char* src);
static const char* get_word();

static int is_odd(const void* n);
static void clone_str(void* dst, const void* src);

TEST test_array_copy(void)
{
    array* a = array_create(42, sizeof(char*));
    for (int i = 0; i < 10; ++i)
        array_insert_at(a, my_strdup(get_word()), i);

    array* b = array_copy(a, clone_str);
    ASSERT_EQ(a->capacity, b->capacity);
    ASSERT_EQ(a->size, b->size);
    ASSERT_EQ(a->DATA_SIZE, b->DATA_SIZE);

    printf("%s : %s\n", (char*)array_at(a, 0), (char*)array_at(a, 1));
    printf("%s : %s\n", (char*)array_at(a, 0), (char*)array_at(b, 1));

    for (int i = 0; i < 10; ++i)
        ASSERT_STR_EQ(array_at(a, i), array_at(b, i));

    char* first_word = array_at(b, 0);
    first_word[0] = 'p';
    ASSERT_NEQ(strcmp(first_word, array_at(a, 0)), 0);
    ASSERT_STR_EQ("pat", array_at(a, 0));


    array_destroy(a, free);
    array_destroy(b, free);
    PASS();
}

TEST test_array_filter(void)
{
    array* a = array_create(42, sizeof(int));
    for (int i = 0; i < 10; ++i)
        array_push_back(a, &i);

    array* b = array_filter(a, is_odd, NULL);
    ASSERT_NEQ(NULL, b);
    ASSERT_NEQ(NULL, b->data);
    ASSERT_EQ(5, b->size);
    
    for (int i = 1, j = 0; j < 5; i += 2, ++j)
        ASSERT_EQ(i, *(int*)array_at(b, j));

    array_destroy(a, NULL);
    array_destroy(b, NULL);
    PASS();
};

TEST test_array_create(void)
{
    array* a = array_create(42, sizeof(int));
    ASSERT_NEQ(NULL, a);
    ASSERT_NEQ(NULL, a->data);
    ASSERT_EQ(42, a->capacity);
    ASSERT_EQ(0, a->size);
    ASSERT_EQ(sizeof(int), a->DATA_SIZE);

    array* b = array_create(0, sizeof(int));
    ASSERT_NEQ(NULL, b);
    ASSERT_NEQ(NULL, b->data);
    ASSERT_EQ(0, b->capacity);
    ASSERT_EQ(0, b->size);
    ASSERT_EQ(sizeof(int), b->DATA_SIZE);

    array_destroy(a, NULL);
    array_destroy(b, NULL);
    PASS();
}

SUITE(test_array_creation)
{
    RUN_TEST(test_array_create);
    RUN_TEST(test_array_filter);
    RUN_TEST(test_array_copy);
}

static int is_odd(const void* n)
{
    if (n == NULL) return 0;
    return *(const int*)n % 2;
}
static char* my_strdup(const char* src)
{
    const size_t size = strlen(src);
    char* res = malloc((size + 1) * sizeof(char));
    memcpy(res, src, size * sizeof(char));
    res[size] = '\0';
    return res;
}
static void clone_str(void* dst, const void* src)
{
    const size_t ptr_size = sizeof(char*);
    memcpy(dst, my_strdup(src), ptr_size);
}
static const char* get_word()
{
    static const char* words[] = {"cat", "dog", "bat"};
    static size_t i;
    const char* word = words[i];
    i = (i + 1) % (sizeof(words) / sizeof(*words));
    return word;
}
