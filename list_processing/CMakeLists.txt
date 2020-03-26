configure_file(config.hpp.in config.hpp)

add_library(library dynamic/Range.cpp)
set_target_properties(library
  PROPERTIES
  CXX_STANDARD 17)
target_include_directories(library
  PUBLIC
  $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}>
  $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}>
  $<INSTALL_INTERFACE:${list_processing_INSTALL_INCLUDEDIR}>)

target_link_libraries(library
  INTERFACE
  type_utility::type_utility)

add_library(ListProcessing::library ALIAS library)

add_executable(config
  config.cpp
  config/Driver.hpp config/Driver.cpp
  config/ExceptionHandler.hpp config/ExceptionHandler.cpp)
set_target_properties(config
  PROPERTIES
  CXX_STANDARD 17)


target_link_libraries(config
  PRIVATE ListProcessing::library)
  
install(TARGETS library config
  EXPORT list_processing_EXPORTS
  RUNTIME DESTINATION ${list_processing_INSTALL_BINDIR}
  LIBRARY DESTINATION ${list_processing_INSTALL_LIBDIR}
  ARCHIVE DESTINATION ${list_processing_INSTALL_LIBDIR})

install(FILES
  ${CMAKE_CURRENT_BINARY_DIR}/config.hpp
  compile_time.hpp
  dynamic.hpp
  DESTINATION ${list_processing_INSTALL_INCLUDEDIR}/list_processing)

install(DIRECTORY
  ${CMAKE_CURRENT_SOURCE_DIR}/compile_time
  ${CMAKE_CURRENT_SOURCE_DIR}/dynamic
  DESTINATION ${list_processing_INSTALL_INCLUDEDIR}/list_processing)
