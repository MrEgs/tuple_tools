cmake_minimum_required(VERSION 3.1)
project(tuple_tools)

set(CMAKE_CXX_STANDARD 14)

option(BUILD_TESTS "Build and execute unit tests" ON)

if (BUILD_TESTS)
  enable_testing()

  function(make_test component_name)
    add_executable(${component_name}_test ${component_name}_test.cpp)
    add_test(${component_name} ${component_name}_test)
  endfunction()
  
else()
  # provide empty make_test function
  function(make_test component_name)
  endfunction()

endif (BUILD_TESTS)


add_subdirectory(tuple_tools)

