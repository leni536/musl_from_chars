// Copyright (C) 2020-2024 Free Software Foundation, Inc.
//
// This file is part of the GNU ISO C++ Library.  This library is free
// software; you can redistribute it and/or modify it under the
// terms of the GNU General Public License as published by the
// Free Software Foundation; either version 3, or (at your option)
// any later version.

// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License along
// with this library; see the file COPYING3.  If not see
// <http://www.gnu.org/licenses/>.

// { dg-do run { target c++23 } }
// { dg-add-options ieee }
// { dg-additional-options "-DSKIP_LONG_DOUBLE" { target aarch64-*-vxworks* } }

#include <charconv>
#include <string>
#include <limits>
#include <stdfloat>
#include <cmath>
#include <cstdlib>
#include <cassert>
#define VERIFY assert

#include <musl_from_chars/from_chars.h>
namespace mfc = musl_from_chars;

// Test mfc::from_chars floating-point conversions.

#if __cpp_lib_to_chars >= 201611L
#if defined(__STDCPP_FLOAT64_T__) && defined(_GLIBCXX_DOUBLE_IS_IEEE_BINARY64)
void
test01()
{
  std::string s;
  std::float64_t f64;
  std::from_chars_result res;

  for (auto fmt : { mfc::chars_format::fixed, mfc::chars_format::scientific,
		    mfc::chars_format::general, mfc::chars_format::hex })
  {
    s = "Info";
    res = mfc::from_chars(s.data(), s.data() + s.length(), f64, fmt);
    VERIFY( std::isinf(f64) );
    VERIFY( res.ptr == s.data() + 3 );
    VERIFY( res.ec == std::errc{} );

    s = "-INFIN";
    res = mfc::from_chars(s.data(), s.data() + s.length(), f64, fmt);
    VERIFY( std::isinf(f64) );
    VERIFY( f64 < 0 );
    VERIFY( res.ptr == s.data() + 4 );
    VERIFY( res.ec == std::errc{} );

    s = "InFiNiTy aNd BeYoNd";
    res = mfc::from_chars(s.data(), s.data() + s.length(), f64, fmt);
    VERIFY( std::isinf(f64) );
    VERIFY( res.ptr == s.data() + 8 );
    VERIFY( res.ec == std::errc{} );

    s = "nAn";
    res = mfc::from_chars(s.data(), s.data() + s.length(), f64, fmt);
    VERIFY( std::isnan(f64) );
    VERIFY( res.ptr == s.data() + 3 );
    VERIFY( res.ec == std::errc{} );

    s = "-NAN()";
    res = mfc::from_chars(s.data(), s.data() + s.length(), f64, fmt);
    VERIFY( std::isnan(f64) );
    VERIFY( res.ptr == s.data() + s.length() );
    VERIFY( res.ec == std::errc{} );
  }
}

void
test02()
{
  std::string s;
  std::float64_t f64 = 1.0f64;
  std::from_chars_result res;

  s = "0x123";
  res = mfc::from_chars(s.data(), s.data() + s.length(), f64);
  VERIFY( f64 == 0.0f64 );
  VERIFY( res.ptr == s.data() + 1 );
  VERIFY( res.ec == std::errc{} );

  f64 = 1.0f64;
  res = mfc::from_chars(s.data(), s.data() + s.length(), f64,
			mfc::chars_format::fixed);
  VERIFY( f64 == 0.0f64 );
  VERIFY( res.ptr == s.data() + 1 );
  VERIFY( res.ec == std::errc{} );

  f64 = 1.0f64;
  res = mfc::from_chars(s.data(), s.data() + s.length(), f64,
			mfc::chars_format::scientific);
  VERIFY( f64 == 1.0f64 );
  VERIFY( res.ptr == s.data() );
  VERIFY( res.ec == std::errc::invalid_argument );

  f64 = 1.0f64;
  res = mfc::from_chars(s.data(), s.data() + s.length(), f64,
			mfc::chars_format::general);
  VERIFY( f64 == 0.0f64 );
  VERIFY( res.ptr == s.data() + 1 );
  VERIFY( res.ec == std::errc{} );

  f64 = 1.0f64;
  res = mfc::from_chars(s.data(), s.data() + s.length(), f64,
			mfc::chars_format::hex);
  VERIFY( f64 == 0.0f64 );
  VERIFY( res.ptr == s.data() + 1 );
  VERIFY( res.ec == std::errc{} );
}

void
test03()
{
  std::string s;
  std::float64_t f64 = 1.0f64;
  std::from_chars_result res;

  s = "0.5e+2azzz";
  res = mfc::from_chars(s.data(), s.data() + s.length(), f64);
  VERIFY( f64 == 0.5e+2f64 );
  VERIFY( res.ptr == s.data() + s.length() - 1 - 3 );
  VERIFY( res.ec == std::errc{} );

  res = mfc::from_chars(s.data(), s.data() + s.length(), f64,
			mfc::chars_format::fixed);
  VERIFY( f64 == 0.5f64 );
  VERIFY( res.ptr == s.data() + 3 );
  VERIFY( res.ec == std::errc{} );

  f64 = 1.0f64;
  res = mfc::from_chars(s.data(), s.data() + s.length(), f64,
			mfc::chars_format::scientific);
  VERIFY( f64 == 0.5e+2f64 );
  VERIFY( res.ptr == s.data() + s.length() - 1 - 3 );
  VERIFY( res.ec == std::errc{} );

  f64 = 1.0f64;
  res = mfc::from_chars(s.data(), s.data() + s.length(), f64,
			mfc::chars_format::general);
  VERIFY( f64 == 0.5e+2f64 );
  VERIFY( res.ptr == s.data() + s.length() - 1 - 3 );
  VERIFY( res.ec == std::errc{} );

  f64 = 1.0;
  res = mfc::from_chars(s.data(), s.data() + s.length(), f64,
			mfc::chars_format::hex);
  VERIFY( f64 == 0x0.5Ep0f64 );
  VERIFY( res.ptr == s.data() + 4 );
  VERIFY( res.ec == std::errc{} );

  s = "1.Ap-2zzz";
  res = mfc::from_chars(s.data(), s.data() + s.length(), f64,
			mfc::chars_format::hex);
  VERIFY( f64 == 0.40625f64 );
  VERIFY( res.ptr == s.data() + s.length() - 3 );
  VERIFY( res.ec == std::errc{} );
}

void
test04()
{
  // Huge input strings
  std::string s(1000, '0');
  std::float64_t f64 = 1.0f64;
  std::from_chars_result res;
  res = mfc::from_chars(s.data(), s.data() + s.length(), f64);
  VERIFY( res.ptr == s.data() + s.length() );
  VERIFY( res.ec == std::errc{} );
  VERIFY( f64 == 0.0f64 );

  s += ".5";
  res = mfc::from_chars(s.data(), s.data() + s.length(), f64);
  VERIFY( res.ptr == s.data() + s.length() );
  VERIFY( res.ec == std::errc{} );
  VERIFY( f64 == 0.5f64 );

  s += "e2";
  auto len = s.length();
  s += std::string(1000, 'a');
  res = mfc::from_chars(s.data(), s.data() + s.length(), f64);
  VERIFY( res.ptr == s.data() + len );
  VERIFY( res.ec == std::errc{} );
  VERIFY( f64 == 50.f64 );
}
#endif

using std::to_string;

#ifdef __GLIBCXX_TYPE_INT_N_0
std::string
to_string(unsigned __GLIBCXX_TYPE_INT_N_0 val)
{
  using Limits = std::numeric_limits<unsigned __GLIBCXX_TYPE_INT_N_0>;
  std::string s(Limits::digits10+2, '0');
  for (auto iter = s.end(); val != 0; val /= 10)
    *--iter = '0' + (val % 10);
  return s;
}
#endif

template<typename FloatT>
void
test_small_num()
{
  std::from_chars_result res;
  FloatT flt;

  // Small integer values that are exactly representable

  for (int i = 0; i < 100; ++i)
  {
    std::string s = to_string(i);
    int len = s.length();
    s += "123";
    const char* s1 = s.c_str();
    const char* s1_end = s1 + len;

    for (auto fmt : { mfc::chars_format::fixed,
		      mfc::chars_format::general,
		      mfc::chars_format::hex })
    {
      if (fmt == mfc::chars_format::hex && i > 9)
	continue;

      res = mfc::from_chars(s1, s1_end, flt, fmt);
      VERIFY( res.ec == std::errc{} );
      VERIFY( res.ptr == s1_end );
      VERIFY( flt == i );
    }

    if (i > 9)
      continue;

    // Test single-digit integers with small exponents.

    const char s2[] = { '.', *s1, 'e', '0', '0', '0', '1' };
    const char* s2_end = s2 + sizeof(s2);

    const char s3[] = { *s1, '0', 'e', '-', '0', '0', '1' };
    const char* s3_end = s3 + sizeof(s3);

    for (auto fmt : { mfc::chars_format::scientific,
		      mfc::chars_format::general })
    {
      res = mfc::from_chars(s2, s2_end, flt, fmt);
      VERIFY( res.ec == std::errc{} );
      VERIFY( res.ptr == s2_end );
      VERIFY( flt == i );

      res = mfc::from_chars(s3, s3_end, flt, fmt);
      VERIFY( res.ec == std::errc{} );
      VERIFY( res.ptr == s3_end );
      VERIFY( flt == i );
    }
  }
}

void
test05()
{
#if defined(__STDCPP_FLOAT32_T__) && defined(_GLIBCXX_FLOAT_IS_IEEE_BINARY32)
  test_small_num<std::float32_t>();
#endif
#if defined(__STDCPP_FLOAT64_T__) && defined(_GLIBCXX_DOUBLE_IS_IEEE_BINARY64)
  test_small_num<std::float64_t>();
#endif
#if defined(__STDCPP_FLOAT128_T__) && defined(_GLIBCXX_LDOUBLE_IS_IEEE_BINARY128)
  test_small_num<std::float128_t>();
#endif
}

template<typename FloatT, typename UIntT>
void
test_max_mantissa()
{
  using Float_limits = std::numeric_limits<FloatT>;
  using UInt_limits = std::numeric_limits<UIntT>;

  if (Float_limits::is_iec559 && Float_limits::digits < UInt_limits::digits)
  {
#ifdef _GLIBCXX_USE_C99_MATH_FUNCS
    std::printf("Testing %d-bit float, using %zu-bit integer\n",
	Float_limits::digits + (int)std::log2(Float_limits::max_exponent) + 1,
	sizeof(UIntT) * __CHAR_BIT__);
#endif

    std::from_chars_result res;
    FloatT flt;

    for (int i = 0; i < 10; ++i)
    {
      // (1 << digits) - 1 is the maximum value of the mantissa
      const auto val = ((UIntT)1 << Float_limits::digits) - 1 - i;
      std::string s = to_string(val);
      auto len = s.length();
      s += "000"; // these should be ignored
      for (auto fmt : { mfc::chars_format::fixed,
			mfc::chars_format::general })
      {
	res = mfc::from_chars(s.data(), s.data() + len, flt, fmt);
	VERIFY( res.ec == std::errc{} );
	VERIFY( res.ptr == s.data() + len );
	VERIFY( flt == val );
      }
      s.resize(len);
      const auto orig_len = len;
      s += "e+000";
      len = s.length();
      s += "111";
      for (auto fmt : { mfc::chars_format::scientific,
			mfc::chars_format::general })
      {
	res = mfc::from_chars(s.data(), s.data() + len, flt, fmt);
	VERIFY( res.ec == std::errc{} );
	VERIFY( res.ptr == s.data() + len );
	VERIFY( flt == val );

	std::string s2 = s.substr(0, len - 5);
	s2.insert(s2.begin() + orig_len - 1, '.');
	s2 += "e000000000001";
	res = mfc::from_chars(s.data(), s.data() + len, flt, fmt);
	VERIFY( res.ec == std::errc{} );
	VERIFY( res.ptr == s.data() + len );
	VERIFY( flt == val );
      }
    }
  }
}

void
test06()
{
#if defined(__STDCPP_FLOAT32_T__) && defined(_GLIBCXX_FLOAT_IS_IEEE_BINARY32)
  test_max_mantissa<std::float32_t, unsigned long>();
#endif
#if defined(__STDCPP_FLOAT64_T__) && defined(_GLIBCXX_DOUBLE_IS_IEEE_BINARY64)
  test_max_mantissa<std::float64_t, unsigned long long>();
#endif
#if defined(__GLIBCXX_TYPE_INT_N_0) && !defined SKIP_LONG_DOUBLE \
    && defined(__STDCPP_FLOAT128_T__) && defined(_GLIBCXX_LDOUBLE_IS_IEEE_BINARY128)
  test_max_mantissa<std::float128_t, unsigned __GLIBCXX_TYPE_INT_N_0>();
#endif
}
#endif

int
main()
{
#if __cpp_lib_to_chars >= 201611L
#if defined(__STDCPP_FLOAT64_T__) && defined(_GLIBCXX_DOUBLE_IS_IEEE_BINARY64)
  test01();
  test02();
  test03();
  test04();
#endif
  test05();
  test06();
#endif
}
