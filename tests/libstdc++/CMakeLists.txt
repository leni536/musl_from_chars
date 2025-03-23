add_executable(
  test-libstdc++-4
  4.cc
)

target_link_libraries(
  test-libstdc++-4
  PUBLIC
  musl_from_chars
)
