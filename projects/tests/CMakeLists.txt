set(target_name tests)

add_executable(
    ${target_name}
    time.cpp
    ${PROJECT_SOURCE_DIR}/projects/include/OPoverload/time.hpp
    soundex.cpp
    ${PROJECT_SOURCE_DIR}/projects/include/soundex/soundex.hpp
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
