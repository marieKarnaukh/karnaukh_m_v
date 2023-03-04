cmake_minimum_required (VERSION 3.8)

set_property(GLOBAL PROPERTY USE_FOLDERS ON) # after 3.26 ON by default
set_property(GLOBAL PROPERTY PREDEFINED_TARGETS_FOLDER "cmake")

project ("rational")

find_package(doctest CONFIG REQUIRED)

#include_directories (RationalLibrary)
add_subdirectory (rational)
add_subdirectory (test)


