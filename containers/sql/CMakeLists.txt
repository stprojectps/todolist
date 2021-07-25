# memop cmake

add_library(sql
    src/sql.c
)

target_link_libraries(sql
    common
    memop
)

target_include_directories(sql
    PUBLIC include
)
