#include <musl_from_chars/floatscan.h>

#include <iostream>

namespace {

struct my_string_view : std::string_view {
  using std::string_view::string_view;

  int err = 0;
};

} // anonymous_namespace

int main() {
  using enum musl_from_chars::chars_format;
  std::cout << std::hexfloat;
  {
    constexpr float res = []{
      my_string_view sv = "0.2";
      return musl_from_chars::detail::__floatscan(sv, 0, 1, general);
    }();
    std::cout << "1/5 float: " << res << std::endl;
  }

  {
    constexpr double res = []{
      my_string_view sv = "0.2";
      return musl_from_chars::detail::__floatscan(sv, 1, 1, general);
    }();
    std::cout << "1/5 double: " << res << std::endl;
  }

  {
    constexpr long double res = []{
      my_string_view sv = "0.2";
      return musl_from_chars::detail::__floatscan(sv, 2, 1, general);
    }();
    std::cout << "1/5 long double: " << res << std::endl;
  }
}
