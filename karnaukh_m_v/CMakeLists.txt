cmake_minimum_required (VERSION 3.8)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set_property(GLOBAL PROPERTY PREDEFINED_TARGETS_FOLDER "cmake")

project ("arrayD")

find_package(doctest CONFIG REQUIRED)

add_subdirectory (prj.lab)
add_subdirectory (prj.test)
