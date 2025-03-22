#ifndef MUSL_FROM_CHARS_CHARS_FORMAT_H
#define MUSL_FROM_CHARS_CHARS_FORMAT_H

#include <charconv>
#include <utility>
#include <bit>

namespace musl_from_chars {

enum class chars_format : std::underlying_type_t<std::chars_format> {
  scientific = std::to_underlying(std::chars_format::scientific),
  fixed = std::to_underlying(std::chars_format::fixed),
  hex = std::to_underlying(std::chars_format::hex),
  general = fixed | scientific,
  strtod
  = (
    1 << std::countr_one(
        static_cast<
          std::make_unsigned_t<std::underlying_type_t<std::chars_format>>
        >(
          std::chars_format::scientific
          | std::chars_format::fixed
          | std::chars_format::hex
        )
    )
  ),
};

} // namespace musl_from_chars
#endif // MUSL_FROM_CHARS_CHARS_FORMAT_H
