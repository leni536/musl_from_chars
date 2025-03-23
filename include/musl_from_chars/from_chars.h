#ifndef MUSL_FROM_CHARS_FROM_CHARS_H
#define MUSL_FROM_CHARS_FROM_CHARS_H

#include <charconv>
#include <cfenv>
#include <utility>

#include "chars_format.h"
#include "floatscan.h"
#include "fake_file.h"

namespace musl_from_chars {

namespace detail {

template <typename T>
inline constexpr int precision = 3;

template <>
inline constexpr int precision<float> = 0;

template <>
inline constexpr int precision<double> = 1;

template <>
inline constexpr int precision<long double> = 2;

constexpr std::from_chars_result
from_chars_impl(const char* first, const char* last, auto& value, chars_format fmt) {
  struct rounding_guard {
    int rounding;
    constexpr rounding_guard() {
      if !consteval {
        rounding = std::fegetround();
        if (rounding != FE_TONEAREST) {
          std::fesetround(FE_TONEAREST);
        }
      }
    }
    constexpr ~rounding_guard() {
      if !consteval{
        if (rounding != FE_TONEAREST) {
          std::fesetround(rounding);
        }
      }
    }
  } guard;

  auto input = fake_file{
    .view{first, last}
  };
  const auto res = __floatscan(input, precision<std::remove_reference_t<decltype(value)>>, 1, fmt);
  switch (input.err) {
    case 0:
        value = res;
        return {.ptr = input.view.data()};
    case EINVAL:
        return {
          .ptr = first,
          .ec = std::errc::invalid_argument,
        };
    case ERANGE:
        return {
          .ptr = input.view.data(),
          .ec = std::errc::result_out_of_range,
        };
  }
  std::unreachable();
}

std::from_chars_result
from_chars_nonconst(const char* first, const char* last, auto& value, chars_format fmt) {
  return from_chars_impl(first, last, value, fmt);
}

extern template std::from_chars_result from_chars_nonconst(const char*, const char*, float&, chars_format);
extern template std::from_chars_result from_chars_nonconst(const char*, const char*, double&, chars_format);
extern template std::from_chars_result from_chars_nonconst(const char*, const char*, long double&, chars_format);

constexpr std::from_chars_result
from_chars_impl2(const char* first, const char* last, auto& value, chars_format fmt) {
  if consteval {
    return from_chars_impl(first, last, value, fmt);
  } else {
    return from_chars_nonconst(first, last, value, fmt);
  }
}

} // namespace detail

constexpr std::from_chars_result
from_chars(const char* first, const char* last, float& value, chars_format fmt = chars_format::general) {
  return detail::from_chars_impl2(first, last, value, fmt);
}

constexpr std::from_chars_result
from_chars(const char* first, const char* last, double& value, chars_format fmt = chars_format::general) {
  return detail::from_chars_impl2(first, last, value, fmt);
}

constexpr std::from_chars_result
from_chars(const char* first, const char* last, long double& value, chars_format fmt = chars_format::general) {
  return detail::from_chars_impl2(first, last, value, fmt);
}

} // namespace musl_from_chars

#endif // MUSL_FROM_CHARS_FROM_CHARS_H
