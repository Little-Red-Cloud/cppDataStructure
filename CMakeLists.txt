cmake_minimum_required(VERSION 3.20.0)

project(CPPDataStructure)

set(LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)
add_executable(01 01.cpp)

set(myLibrariesSources
    "./include/myLibraries.h"
    02TimeCounting.cpp
    )

add_library(myLibraries STATIC ${myLibrariesSources})
target_include_directories(myLibraries PUBLIC ${PROJECT_SOURCE_DIR}/include)

add_library(myLibraries_interface INTERFACE)
target_link_libraries(myLibraries_interface INTERFACE myLibraries)

set_target_properties(myLibraries PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ${LIBRARY_OUTPUT_DIRECTORY})


add_executable(02test 02testTimeCounting.cpp)
target_link_libraries(02test PUBLIC myLibraries_interface)

add_executable(03test 03testTree.cpp)
target_link_libraries(03test PUBLIC myLibraries_interface)

add_executable(04test 04testMySort.cpp)
target_link_libraries(04test PUBLIC myLibraries_interface)