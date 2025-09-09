#include "tests.h"

GREATEST_MAIN_DEFS();

int main(int argc, char **argv) {
    GREATEST_MAIN_BEGIN();

    RUN_TEST(test_array_initialization);
    RUN_TEST(test_array_insertion);

    GREATEST_MAIN_END();
}