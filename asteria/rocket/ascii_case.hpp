// This file is part of Asteria.
// Copyleft 2018 - 2020, LH_Mouse. All wrongs reserved.

#ifndef ROCKET_ASCII_CASE_HPP_
#define ROCKET_ASCII_CASE_HPP_

#include "utilities.hpp"

namespace rocket {

#include "details/ascii_case.ipp"

// Classification
constexpr
bool
ascii_is_alpha(char c)
noexcept
  { return details_ascii_case::cmask_of(c) != 0;  }

constexpr
bool
ascii_is_upper(char c)
noexcept
  { return details_ascii_case::cmask_of(c) == 1;  }

constexpr
bool
ascii_is_lower(char c)
noexcept
  { return details_ascii_case::cmask_of(c) == 2;  }

// Conversion
constexpr
char
ascii_to_upper(char c)
noexcept
  { return static_cast<char>(details_ascii_case::to_upper(c));  }

constexpr
char
ascii_to_lower(char c)
noexcept
  { return static_cast<char>(details_ascii_case::to_lower(c));  }

// Comparison
constexpr
bool
ascii_ci_equal(char x, char y)
noexcept
  { return details_ascii_case::to_lower(x) ==
           details_ascii_case::to_lower(y);  }

constexpr
bool
ascii_ci_equal(const char* sx, size_t nx, const char* sy, size_t ny)
noexcept
  {
    // If the lengths are unequal, the strings cannot be equal.
    if(nx != ny)
      return false;

    // Perform character-wise comparison of two strings of `nx` characters.
    for(size_t k = 0;  k != nx;  ++k)
      if(!noadl::ascii_ci_equal(sx[k], sy[k]))
        return false;

    // All characters are equal.
    return true;
  }

constexpr
int
ascii_ci_compare(char x, char y)
noexcept
  { return static_cast<int>(details_ascii_case::to_lower(x)) -
           static_cast<int>(details_ascii_case::to_lower(y));  }

constexpr
int
ascii_ci_compare(const char* sx, size_t nx, const char* sy, size_t ny)
noexcept
  {
    // Compare the longest initial substring.
    // If any characters compare unequal, return immediately.
    size_t n = noadl::min(nx, ny);

    for(size_t k = 0;  k != n;  ++k)
      if(int r = noadl::ascii_ci_compare(sx[k], sy[k]))
        return r;

    // The substrings compare equal.
    // Compare the lengths. Note this is not very correct when both lengths
    // are greater than `PTRDIFF_MAX / 2`, which is however impractical.
    return static_cast<int>(static_cast<ptrdiff_t>(nx - ny));
  }

// Hash
constexpr
size_t
ascii_ci_hash(const char* s, size_t n)
noexcept
  {
    // Implement the FNV-1a hash algorithm.
    uint32_t reg = 0x811C9DC5;
    for(size_t k = 0;  k != n;  ++k)
      reg = (reg ^ details_ascii_case::to_lower(s[k])) * 0x1000193;
    return reg;
  }

}  // namespace rocket

#endif
