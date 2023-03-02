cmake_minimum_required (VERSION 3.8)

project ("arrayD")


include_directories (arrayDLibrary)
add_subdirectory (arrayDLibrary)
add_subdirectory (test)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET arrayD PROPERTY CXX_STANDARD 20)
endif()
