configure_file(config.hpp.in config.hpp)

add_library(list_processing INTERFACE)
target_include_directories(list_processing
  INTERFACE
  $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}>
  $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}>
  $<INSTALL_INTERFACE:${list_processing_INSTALL_INCLUDEDIR}>)

add_library(list_processing::list_processing ALIAS list_processing)
  
install(TARGETS list_processing
  EXPORT list_processing_EXPORTS
  RUNTIME DESTINATION ${list_processing_INSTALL_BINDIR}
  LIBRARY DESTINATION ${list_processing_INSTALL_LIBDIR}
  ARCHIVE DESTINATION ${list_processing_INSTALL_LIBDIR})

install(FILES
  ${CMAKE_CURRENT_BINARY_DIR}/config.hpp
  DESTINATION ${list_processing_INSTALL_INCLUDEDIR})
