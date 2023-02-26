
add_library (RationalLibrary rational.hpp rational.cpp)
#set_property(TARGET RationalLibrary PROPERTY CXX_STANDARD 20)
#target_include_directories(RationalLibrary PUBLIC
#  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
#  $<INSTALL_INTERFACE:include>
#)
#install(TARGETS RationalLibrary)