# © 2021 Joseph Cameron - All Rights Reserved

cmake_minimum_required(VERSION 3.9 FATAL_ERROR)

project(null)

include("${CMAKE_CURRENT_SOURCE_DIR}/cmake/jfc-cmake/jfclib.cmake")

option(JFC_BUILD_DOCS "Build documentation" OFF)
option(JFC_BUILD_TESTS "Build unit tests" OFF)

add_subdirectory(thirdparty)

jfc_project(executable
    NAME "prettyjson"
    VERSION 0.0
    DESCRIPTION "json pretty print filter"
    C++_STANDARD 17
    C_STANDARD 90

    PUBLIC_INCLUDE_DIRECTORIES
        ${CMAKE_CURRENT_SOURCE_DIR}/include
#        ${dependencyname_INCLUDE_DIRECTORIES} 


    PRIVATE_INCLUDE_DIRECTORIES
        ${CMAKE_CURRENT_SOURCE_DIR}/src/include

#    LIBRARIES
#        ${dependencyname_LIBRARIES} 

    SOURCE_LIST
        ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp

#    DEPENDENCIES
#        "dependencyname"
)

if (JFC_BUILD_TESTS)
    add_subdirectory(test)
endif()

if (JFC_BUILD_DOCS)
    add_subdirectory(docs)
endif()
