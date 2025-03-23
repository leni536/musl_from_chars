#include <musl_from_chars/fake_file.h>
#include <musl_from_chars/floatscan.h>

#include <iostream>

using musl_from_chars::detail::fake_file;

int main() {
  using enum musl_from_chars::chars_format;
  std::cout << std::hexfloat;
  {
    constexpr float res = []{
      fake_file input{.view = "0.2"};
      return musl_from_chars::detail::__floatscan(input, 0, 1, general);
    }();
    std::cout << "1/5 float: " << res << std::endl;
  }

  {
    constexpr double res = []{
      fake_file input{.view = "0.2"};
      return musl_from_chars::detail::__floatscan(input, 1, 1, general);
    }();
    std::cout << "1/5 double: " << res << std::endl;
  }

  {
    constexpr long double res = []{
      fake_file input{.view = "0.2"};
      return musl_from_chars::detail::__floatscan(input, 2, 1, general);
    }();
    std::cout << "1/5 long double: " << res << std::endl;
  }
}
