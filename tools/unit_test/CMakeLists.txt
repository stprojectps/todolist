# unit_test cmake

add_library(unit
    src/unit_test.c
)

target_link_libraries(unit
)

target_include_directories(unit
    PUBLIC include
)
