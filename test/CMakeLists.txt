# test

set(TEST src)
set(EXEC_NAME unit_test)

#unit test for sql
if(BUILD_SQL_TEST)
    set(TEST ${TEST}/sql)
    set(EXEC_NAME sql_units)
endif(BUILD_SQL_TEST)

# directives for building test
add_executable(${EXEC_NAME}
    ${TEST}/main.c
)

target_link_libraries(${EXEC_NAME}
    vector
    sql
    unit
    tools
)

target_include_directories(${EXEC_NAME}
    PUBLIC include
)
