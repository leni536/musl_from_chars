# musl_from_chars
`musl_from_chars::from_chars` is a `constexpr` implementation of C++'s `from_chars` function from `<charconv>`,
  with the primary goal of supporting [P3652](https://wg21.link/P3652) with implementation experience.

The implementation is based on musl's implementation of `strtod`, trying to keep modifications to a minimum.

I recommend a shallow clone when checkout out the repository, as it includes the full history of musl and gcc.

## Goals
* Correctly implement C++'s `from_chars` as specified.
  * This should be supported by an extensive test suite.
* Support `float`, `double` and `long double`.
* Support all other binary floating point types.
* Support evaluation within constant expressions.
* Minimizing compilation overhead of making `from_chars` available for constant expressions.
  * Including and using the header should be virtually free when `from_chars` is not used in constant expressions.
  * Using `from_char` in constant expressions should have reasonable performance.

## Non-goals
* Competitive performance for runtime evaluation.
  * Your standard library's implementation and [fastfloat/fast_float](https://github.com/fastfloat/fast_float) are faster.
* Support for decimal floating point.
* Maintaining a production library.
