cmake_minimum_required (VERSION 3.8)

project(rational)

include_directories (RationalLibrary)

add_subdirectory (RationalLibrary)
add_subdirectory (test)
include_directories(doctest)

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT myRat)



