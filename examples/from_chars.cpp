#include <musl_from_chars/from_chars.h>

#include <iostream>
#include <string_view>

namespace mfc = musl_from_chars;

int main() {
  constexpr auto d = []{
    const auto sv = std::string_view("3.141592654");
    double ret;

    mfc::from_chars(
        sv.data(),
        sv.data() + sv.size(),
        ret,
        mfc::chars_format::general
    );
    return ret;
  }();
  std::cout << d << std::endl;
}
