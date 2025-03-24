add_executable(
  test-libstdc++-4
  4.cc
)

target_link_libraries(
  test-libstdc++-4
  PUBLIC
  musl_from_chars
)

add_executable(
  test-libstdc++-5
  5.cc
)

target_link_libraries(
  test-libstdc++-5
  PUBLIC
  musl_from_chars
)

add_executable(
  test-libstdc++-6
  6.cc
)

target_link_libraries(
  test-libstdc++-6
  PUBLIC
  musl_from_chars
)

add_executable(
  test-libstdc++-7
  7.cc
)

target_link_libraries(
  test-libstdc++-7
  PUBLIC
  musl_from_chars
)
