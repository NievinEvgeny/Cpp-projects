set(target_name OPoverload-tests)

add_executable(
    ${target_name}
    time.cpp
    ${PROJECT_SOURCE_DIR}/projects/include/OPoverload/time.hpp
)

include(CompileOptions)
set_compile_options(${target_name})

target_link_libraries(
    ${target_name}
    PRIVATE
    GTest::gtest_main
)

target_include_directories(
    ${target_name}
    PUBLIC
    ${PROJECT_SOURCE_DIR}/projects/include/
)

include(GoogleTest)
gtest_discover_tests(${target_name})
