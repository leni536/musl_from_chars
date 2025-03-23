#ifndef MUSL_FROM_CHARS_FAKE_FILE_H
#define MUSL_FROM_CHARS_FAKE_FILE_H

#include <string_view>

namespace musl_from_chars::detail {

struct fake_file {
  std::string_view view;
  int err{};
  bool eof_reached = false;
};

} // namespace musl_from_chars::detail

#endif // MUSL_FROM_CHARS_FAKE_FILE_H
