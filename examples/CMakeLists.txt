add_executable(
  example-floatscan
  floatscan.cpp
)

target_link_libraries(
  example-floatscan
  PUBLIC
  musl_from_chars
)

add_executable(
  example-from_chars
  from_chars.cpp
)

target_link_libraries(
  example-from_chars
  PUBLIC
  musl_from_chars
)
