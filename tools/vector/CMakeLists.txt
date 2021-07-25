# vector cmake


add_library(vector
    src/vector_base.c
)

target_link_libraries(vector
)

target_include_directories(vector
    PUBLIC include
)