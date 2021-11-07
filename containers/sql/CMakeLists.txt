# memop cmake

#SQLite3 lib is needed
find_package (SQLite3 REQUIRED)

add_library(sql
    src/sql.c
)

target_link_libraries(sql PUBLIC
    common
    memop
    SQLite3
)

target_include_directories(sql
    PUBLIC include ${SQLITE3_INCLUDE_DIRS}
)
