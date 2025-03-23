#include <musl_from_chars/from_chars.h>

namespace musl_from_chars::detail {

template std::from_chars_result from_chars_nonconst(const char*, const char*, float&, chars_format);
template std::from_chars_result from_chars_nonconst(const char*, const char*, double&, chars_format);
template std::from_chars_result from_chars_nonconst(const char*, const char*, long double&, chars_format);

} // namespace musl_from_chars::detail
