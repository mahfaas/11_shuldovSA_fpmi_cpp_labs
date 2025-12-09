set(TEST_SOURCES
    mersenne_tests.cpp
)

add_executable(mersenne_tests ${TEST_SOURCES})

target_link_libraries(mersenne_tests
    PRIVATE
        mersenne_lib
        gtest
        gtest_main
)

add_test(NAME MersenneTests COMMAND mersenne_tests)
