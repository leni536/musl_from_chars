cmake_minimum_required(VERSION 3.25)
project(musl_from_chars)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(
  musl_from_chars
  STATIC
  src/from_chars.cpp
)

target_include_directories(
  musl_from_chars
  PUBLIC
  include
)

add_subdirectory(examples)
add_subdirectory(tests)
