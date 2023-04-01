set(target_name tests)

add_executable(
    ${target_name}
    time.cpp
    ${PROJECT_SOURCE_DIR}/projects/include/OPoverload/time.hpp
    soundex.cpp
    ${PROJECT_SOURCE_DIR}/projects/include/soundex/soundex.hpp
    smartptr.cpp
    ${PROJECT_SOURCE_DIR}/projects/include/smartptr/unique_ptr.hpp
    ${PROJECT_SOURCE_DIR}/projects/include/smartptr/shared_ptr.hpp
)

set_target_properties(
    ${target_name}
    PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS OFF
)

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
