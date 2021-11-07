cmake_minimum_required(VERSION 3.10)

# project name and descriptions
project(TodoList
    VERSION 0.1.0
    DESCRIPTION "\"Todo list app\""
    LANGUAGES C
)

# compilation definition
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED True)

add_compile_options(-W -Wall -pedantic)
option(BUILD_UNIT_TEST "Build unit test" OFF)
option(BUILD_SQL_TEST  "Build sql unit test" OFF)

# Define global variables
# > Project root directory
set(PROJECT_ROOT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR})

# project configuration files
configure_file(config/config.h.ini config.h)

# add subdirectories
add_subdirectory(tools)
add_subdirectory(containers)

# compiling for unit test
if(BUILD_UNIT_TEST)
    add_subdirectory(test)
endif(BUILD_UNIT_TEST)


#installation part; to be consolidate
# install(TARGETS ${EXEC_NAME} DESTINATION ${PROJECT_ROOT_DIRECTORY}/build/bin)
# include(InstallRequiredSystemLibraries)
# set(CPACK_PACKAGE_VERSION_MAJOR "${TodoList_VERSION_MAJOR}")
# set(CPACK_PACKAGE_VERSION_MINOR "${TodoList_VERSION_MINOR}")
# set(CPACK_PACKAGE_VERSION_PATCH "${TodoList_VERSION_PATCH}")
# include(CPack)
