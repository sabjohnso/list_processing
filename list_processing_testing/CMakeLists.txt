find_package(GTest)

macro(list_processing_add_test test_name exe_name)
  add_executable(${exe_name} ${ARGN})
  target_link_libraries(${exe_name} PRIVATE
    list_processing::list_processing
    GTest::gtest_main)
  add_test(${test_name} ${exe_name})
endmacro()
