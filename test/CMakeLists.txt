# test

add_executable(suite
    src/main.c
)

target_link_libraries(suite
    vector
    sql
    unit
    tools
)

target_include_directories(suite
    PUBLIC include
)