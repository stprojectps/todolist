# Cmake for tools

add_library(tools INTERFACE)

target_include_directories(tools
    INTERFACE include
)

add_subdirectory(memop)
add_subdirectory(vector)
if(BUILD_UNIT_TEST)
    add_subdirectory(unit_test)
endif(BUILD_UNIT_TEST)
