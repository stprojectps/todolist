# memop cmake

add_library(core
    src/task.c
    src/todo.c
)

target_link_libraries(core
    common
    memop
    sql
)

target_include_directories(core
    PUBLIC include
)
