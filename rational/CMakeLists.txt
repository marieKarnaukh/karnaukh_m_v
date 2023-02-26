cmake_minimum_required (VERSION 3.8)
#set(-DCMAKE_TOOLCHAIN_FILE=E:/vspkg/vcpkg/scripts/buildsystems/vcpkg.cmake)
project(rational) # project (RationalLib)

#set_property(GLOBAL PROPERTY USE_FOLDERS ON)
#set_property(GLOBAL PROPERTY PREDEFINED_TARGETS_FOLDER "cmake")

include_directories (RationalLibrary)

add_subdirectory (RationalLibrary)
add_subdirectory (test)
include_directories(doctest)
#add_subdirectory (doctest)

#add_executable (myRat rational_test.cpp)

#set(CMAKE_CXX_STANDARD 11)
#set_property(TARGET rational.test PROPERTY CXX_STANDARD 11)
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT myRat)

#target_link_libraries (myRat RationalLibrary)


