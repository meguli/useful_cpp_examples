# The minimum version of CMake necessary to build this project
cmake_minimum_required (VERSION 3.8)

if(MSVC)
  # Force to always compile with W4
  if(CMAKE_CXX_FLAGS MATCHES "/W[0-4]")
    string(REGEX REPLACE "/W[0-4]" "/W4" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
  else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
  endif()
elseif(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
  # Update if necessary
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wno-long-long -pedantic")
endif()

# Look into this dir for headers
include_directories(
	.
    ..
)

file(GLOB PLAYGROUND_TESTS "*.cpp")	

set(test_files tests_main.cpp
			   ${PLAYGROUND_TESTS})
		 
add_executable(playground_test ${test_files})

set_property(TARGET playground_test PROPERTY CXX_STANDARD 17)

add_test(NAME test COMMAND playground_test)