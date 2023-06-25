add_executable(parser argParser.test.cpp)
target_link_libraries(parser argParser::argParser)

install(TARGETS parser DESTINATION bin COMPONENT parser)
