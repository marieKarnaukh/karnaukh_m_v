add_executable(argParser.test argParser.test.cpp)
target_link_libraries(argParser.test argParser::argParser)

install(TARGETS argParser.test DESTINATION argParserLib/test)