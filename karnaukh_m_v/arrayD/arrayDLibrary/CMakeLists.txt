add_library (arrayD include/arrayD/arrayD.hpp arrayD.cpp)

set_property(TARGET arrayD PROPERTY PUBLIC_HEADER arrayD.hpp)
# setting a property: target(executable or library), property(public or private)

# what this things below are doing?
target_include_directories(arrayD PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)
install(TARGETS arrayD)