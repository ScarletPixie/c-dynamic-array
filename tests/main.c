#include "greatest.h"
#include "tests.h"

GREATEST_MAIN_DEFS();

int main(int argc, char **argv) {
    GREATEST_MAIN_BEGIN();

    RUN_SUITE(test_array_creation);
    RUN_SUITE(test_array_modification);

    GREATEST_MAIN_END();
}
