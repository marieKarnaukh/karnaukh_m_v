add_library(matrixs include/matrixs/matrixs.hpp matrixs.cpp)

target_include_directories(matrixs PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)
install(TARGETS matrixs)
