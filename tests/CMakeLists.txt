include(GoogleTest)

find_package(GTest CONFIG REQUIRED)

add_executable(test-oiio-example
    test_args.cpp
    test_iterate.cpp
    test_mandel.cpp
)
target_link_libraries(test-oiio-example PUBLIC mandel GTest::gmock_main)
set_property(TARGET test-oiio-example PROPERTY FOLDER Tests)

gtest_discover_tests(test-oiio-example)
