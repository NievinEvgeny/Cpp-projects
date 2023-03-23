set(target_name libsoundex)

add_library(${target_name} STATIC
    soundex.cpp
    ${PROJECT_SOURCE_DIR}/projects/include/soundex/soundex.hpp
)

include(CompileOptions)
set_compile_options(${target_name})

target_include_directories(
    ${target_name}
    PUBLIC
    ${PROJECT_SOURCE_DIR}/projects/include/
)