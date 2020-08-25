cmake_minimum_required(VERSION 3.12)

project(list_processing VERSION 0.1.0 LANGUAGES C CXX)

option(list_processing_BUILD_TESTING "Build the list_processing tests" ON)
set(list_processing_DEFAULT_CHUNK_SIZE 32 CACHE STRING
  "Default number of elements per chunk for optimized lists")

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

include(GNUInstallDirs)
set(list_processing_INSTALL_BINDIR ${CMAKE_INSTALL_BINDIR})
set(list_processing_INSTALL_LIBDIR ${CMAKE_INSTALL_LIBDIR})
set(list_processing_INSTALL_INCLUDEDIR ${CMAKE_INSTALL_INCLUDEDIR})
set(list_processing_INSTALL_CONFDIR
  ${list_processing_INSTALL_LIBDIR}/cmake/list_processing-${PROJECT_VERSION})

list(INSERT CMAKE_MODULE_PATH 0 ${PROJECT_SOURCE_DIR}/cmake)
include(list_processing_deps)

add_subdirectory(list_processing)

if(list_processing_BUILD_TESTING)
  include(CTest)
  if(BUILD_TESTING)
    add_subdirectory(list_processing_testing)
  endif()
endif()

install(EXPORT list_processing_EXPORTS
  NAMESPACE list_processing::
  FILE list_processing-exports.cmake
  DESTINATION ${list_processing_INSTALL_CONFDIR})

configure_file(list_processing-config.cmake.in list_processing-config.cmake @ONLY)
install(FILES ${PROJECT_BINARY_DIR}/list_processing-config.cmake
  DESTINATION ${list_processing_INSTALL_CONFDIR})
