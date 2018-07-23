cmake_minimum_required(VERSION 3.1)
project(tuple_tools)

set(CMAKE_CXX_STANDARD 14)

option(BUILD_TESTS "Build and execute unit tests" ON)

if (BUILD_TESTS)
  include(CTest)
  enable_testing()

  include(CMake/DownloadGTest.cmake)

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


add_library(tuple_tools INTERFACE)
target_sources(tuple_tools
  INTERFACE ${PROJECT_SOURCE_DIR}/tuple_tools/bind.h
  INTERFACE ${PROJECT_SOURCE_DIR}/tuple_tools/conditional.h
  INTERFACE ${PROJECT_SOURCE_DIR}/tuple_tools/for_each.h
  INTERFACE ${PROJECT_SOURCE_DIR}/tuple_tools/predicative_get.h
  )
target_include_directories(tuple_tools
  INTERFACE ${PROJECT_SOURCE_DIR}
  )

function(make_example example)
  add_executable(${example} ${example}.cpp)
  target_link_libraries(${example} tuple_tools)
endfunction()

add_subdirectory(tuple_tools)
add_subdirectory(examples)

