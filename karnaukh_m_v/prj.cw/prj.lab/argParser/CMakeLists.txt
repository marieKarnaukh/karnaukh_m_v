add_library(argParser argParser.cpp include/argParser/argParser.hpp)
add_library(argParser::argParser ALIAS argParser)

target_include_directories(argParser PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)
#install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} DESTINATION argParserLib)
#install(TARGETS argParser DESTINATION argParserLib)

install(
    TARGETS argParser
    DESTINATION lib
    COMPONENT parser_lib
)
