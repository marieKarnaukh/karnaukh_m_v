set(argParser_LIBRARIES "argParser")
set(argParser_LIBRARY_DIRS "${CMAKE_CURRENT_LIST_DIR}")
set(argParser_INCLUDE_DIRS "${CMAKE_CURRENT_LIST_DIR}/include")

link_directories("${argParser_LIBRARY_DIRS}")

add_library(argParser::argParser INTERFACE IMPORTED)
set_target_properties(argParser::argParser PROPERTIES
  INTERFACE_INCLUDE_DIRECTORIES "${argParser_INCLUDE_DIRS}"
)

target_link_libraries(argParser::argParser INTERFACE ${argParser_LIBRARIES})
