add_library(argParser argParser.cpp include/argParser/argParser.hpp)
add_library(argParser::argParser ALIAS argParser)

set_property(TARGET argParser PROPERTY PUBLIC_HEADER argParser.hpp)

target_include_directories(argParser PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)
install(TARGETS argParser)
