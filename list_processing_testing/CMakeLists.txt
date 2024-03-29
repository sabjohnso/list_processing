find_package(GTest)

macro(list_processing_add_test test_name exe_name)
  add_executable(${exe_name} ${ARGN})
  target_link_libraries(${exe_name}
    PRIVATE list_processing::header GTest::gtest_main)
  set_target_properties(${exe_name} PROPERTIES CXX_STANDARD 20)
  add_test(${test_name} ${exe_name})
endmacro()

list_processing_add_test(compile_time compile_time_test
  compile_time_test.cpp
  compile_time_stack_test.cpp
  compile_time_tape_test.cpp
  compile_time_queue_test.cpp
  compile_time_tree_test.cpp
  compile_time_alist_test.cpp)

list_processing_add_test(dynamic dynamic_test
  dynamic_list_test.cpp
  dynamic_tlist_test.cpp
  dynamic_stack_test.cpp
  dynamic_tape_test.cpp
  dynamic_queue_test.cpp
  dynamic_tree_test.cpp
  dynamic_alist_test.cpp
  dynamic_lazy_test.cpp
  dynamic_stream_test.cpp
  dynamic_tlist_test.cpp
  range_test.cpp
  shared_test.cpp
  dynamic_hash_table_test.cpp)

list_processing_add_test(
  short_list short_list_test short_list_test.cpp)

list_processing_add_test(
  bucket_list bucket_test bucket_test.cpp)
