#ifndef MUSL_FROM_CHARS_SHGETC_H
#define MUSL_FROM_CHARS_SHGETC_H

#include <stdio.h>
#include <string_view>

#ifndef MUSL_FROM_CHARS_AMALGAMATED_INTERFACE
#include "fake_file.h"
#endif

namespace musl_from_chars::detail {

constexpr void shlim(fake_file& f, off_t) noexcept {}

constexpr int shgetc(fake_file& f) noexcept {
  if (f.view.empty()) {
    f.eof_reached = true;
    return EOF;
  }
  int ret = f.view[0];
  f.view.remove_prefix(1);
  return ret;
}

// Precondition: sv.data()-1 is valid
constexpr void shunget(fake_file& f) noexcept {
  if (f.eof_reached) {
    f.eof_reached = false;
    return;
  }
  f.view = std::string_view(f.view.data()-1, f.view.size() + 1);
}

} // namespace musl_from_chars::detail

#endif // MUSL_FROM_CHARS_SHGETC_H
