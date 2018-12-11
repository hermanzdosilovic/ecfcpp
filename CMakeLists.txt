cmake_minimum_required( VERSION 3.12 )
project( ecfcpp LANGUAGES C CXX )

set( CMAKE_CXX_STANDARD 17 )
set( CMAKE_CXX_STANDARD_REQUIRED ON )

set(
    CMAKE_CXX_FLAGS
    "${CMAKE_CXX_FLAGS} -Wall -Wextra \
    -Wold-style-cast -Wuseless-cast -Wnull-dereference \
    -Werror -Wfatal-errors -pedantic -pedantic-errors"
)

add_library( ecfcpp INTERFACE )
target_link_libraries( ecfcpp INTERFACE m )
target_include_directories( ecfcpp INTERFACE ${CMAKE_CURRENT_LIST_DIR}/include )

option( BUILD_EXAMPLES "" OFF )
if ( BUILD_EXAMPLES )
    add_executable( ga_generational_rastrigin ${CMAKE_CURRENT_LIST_DIR}/examples/ga_generational/rastrigin.cpp )
    target_link_libraries( ga_generational_rastrigin PRIVATE ecfcpp )
endif()
