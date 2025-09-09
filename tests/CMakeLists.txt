set(TEST_SOURCES 
    initialization.c
    manipulation.c
    main.c
)

add_executable(array_tests ${TEST_SOURCES})
target_link_libraries(array_tests PRIVATE array)

add_test(NAME array_tests COMMAND array_tests)