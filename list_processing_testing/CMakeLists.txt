find_package(GTest)

macro(list_processing_add_test test_name exe_name)
  add_executable(${exe_name} ${ARGN})
  target_link_libraries(${exe_name}
    PRIVATE list_processing::list_processing GTest::gtest_main)
  set_target_properties(${exe_name} PROPERTIES CXX_STANDARD 17)
  add_test(${test_name} ${exe_name})
endmacro()

list_processing_add_test(
  compile_time compile_time_test compile_time_test.cpp)
list_processing_add_test(dynamic dynamic_test
  dynamic_test.cpp
  dynamic_stack_test.cpp
  dynamic_zipper_test.cpp)
