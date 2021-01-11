configure_file(config.hpp.in config.hpp)

add_library(list_processing_header dynamic/Range.cpp)
set_target_properties(list_processing_header
  PROPERTIES
  CXX_STANDARD 20)
set_target_properties(list_processing_header PROPERTIES EXPORT_NAME header)
target_include_directories(list_processing_header
  PUBLIC
  $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}>
  $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}>
  $<INSTALL_INTERFACE:${list_processing_INSTALL_INCLUDEDIR}>)

target_link_libraries(list_processing_header
  INTERFACE
  type_utility::type_utility)

add_library(list_processing::header ALIAS list_processing_header)

add_executable(list_processing_config
  config.cpp
  config/Driver.hpp config/Driver.cpp
  config/ExceptionHandler.hpp config/ExceptionHandler.cpp)

set_target_properties(list_processing_config
  PROPERTIES
  CXX_STANDARD 17
  OUTPUT_NAME list_processing_config.hpp)

target_link_libraries(list_processing_config PRIVATE list_processing::header)

add_executable(list_processing::config ALIAS list_processing_config)
  
install(TARGETS list_processing_header list_processing_config
  EXPORT list_processing_EXPORTS
  RUNTIME DESTINATION ${list_processing_INSTALL_BINDIR}
  LIBRARY DESTINATION ${list_processing_INSTALL_LIBDIR}
  ARCHIVE DESTINATION ${list_processing_INSTALL_LIBDIR})

install(FILES
  ${CMAKE_CURRENT_BINARY_DIR}/config.hpp
  compile_time.hpp
  dynamic.hpp
  dynamic_alist.hpp
  dynamic_list.hpp
  dynamic_queue.hpp
  dynamic_shared_list.hpp
  dynamic_stack.hpp
  dynamic_stream.hpp
  dynamic_tape.hpp
  dynamic_tree.hpp
  operators.hpp
  DESTINATION ${list_processing_INSTALL_INCLUDEDIR}/list_processing)

install(DIRECTORY
  ${CMAKE_CURRENT_SOURCE_DIR}/compile_time
  ${CMAKE_CURRENT_SOURCE_DIR}/dynamic
  ${CMAKE_CURRENT_SOURCE_DIR}/operators
  DESTINATION ${list_processing_INSTALL_INCLUDEDIR}/list_processing
  FILES_MATCHING PATTERN "*.hpp")
