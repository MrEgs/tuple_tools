cmake_minimum_required(VERSION 3.1)
project(tuple_tools)

set(CMAKE_CXX_STANDARD 14)

option(BUILD_TESTS "Build and execute unit tests" ON)

if (BUILD_TESTS)
  include(CTest)
  enable_testing()

  function(make_test component_name)
    add_executable(${component_name}_test ${component_name}_test.cpp)
    target_link_libraries(${component_name}_test gtest_main)
    add_test(${component_name} ${component_name}_test)
  endfunction()
  
else()
  # provide empty make_test function
  function(make_test component_name)
  endfunction()

endif (BUILD_TESTS)


include(CMake/DownloadGTest.cmake)

add_subdirectory(tuple_tools)

