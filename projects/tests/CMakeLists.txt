set(target_name tests)

add_executable(
    ${target_name}
    time.cpp
    soundex.cpp
    smartptr.cpp
)

include(CompileOptions)
set_compile_options(${target_name})

target_link_libraries(
    ${target_name}
    PRIVATE
    libsoundex
    GTest::gtest_main
)

target_include_directories(
    ${target_name}
    PUBLIC
    ${PROJECT_SOURCE_DIR}/projects/include/
)

include(GoogleTest)
gtest_discover_tests(${target_name})
