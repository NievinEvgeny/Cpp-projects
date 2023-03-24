set(target_name soundex)

add_executable(${target_name})

include(CompileOptions)
set_compile_options(${target_name})

target_sources(
    ${target_name}
    PRIVATE
    main.cpp
)

target_link_libraries(
    ${target_name}
    PRIVATE
    libsoundex
    nlohmann_json::nlohmann_json
)

add_subdirectory(soundex)
