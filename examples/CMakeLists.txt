add_executable(
  example-floatscan
  floatscan.cpp
)

target_link_libraries(
  example-floatscan
  PUBLIC
  musl_from_chars
)
