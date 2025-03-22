#ifndef MUSL_FROM_CHARS_SHGETC_H
#define MUSL_FROM_CHARS_SHGETC_H

#include <stdio.h>
#include <string_view>

namespace musl_from_chars::detail {

constexpr void shlim(std::string_view& sv, off_t) noexcept {}

constexpr int shgetc(std::string_view& sv) noexcept {
  if (sv.empty()) {
    return EOF;
  }
  int ret = sv[0];
  sv.remove_prefix(1);
  return ret;
}

// Precondition: sv.data()-1 is valid
constexpr void shunget(std::string_view& sv) noexcept {
  sv = std::string_view(sv.data()-1, sv.size() + 1);
}

} // namespace musl_from_chars::detail

#endif // MUSL_FROM_CHARS_SHGETC_H
