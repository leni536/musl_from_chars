#include <musl_from_chars/floatscan.h>

#include <iostream>

int main() {
  std::cout << std::hexfloat;
  {
    constexpr float res = []{
      std::string_view sv = "0.2";
      return musl_from_chars::detail::__floatscan(sv, 0, 1);
    }();
    std::cout << "1/5 float: " << res << std::endl;
  }

  {
    constexpr double res = []{
      std::string_view sv = "0.2";
      return musl_from_chars::detail::__floatscan(sv, 1, 1);
    }();
    std::cout << "1/5 double: " << res << std::endl;
  }

  {
    constexpr long double res = []{
      std::string_view sv = "0.2";
      return musl_from_chars::detail::__floatscan(sv, 2, 1);
    }();
    std::cout << "1/5 long double: " << res << std::endl;
  }
}
