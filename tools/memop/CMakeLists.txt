# memop cmake

add_library(memop
    src/memop.c
)

target_link_libraries(memop
)

target_include_directories(memop
    PUBLIC include
)
