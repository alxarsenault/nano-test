/*
 * MIT License
 *
 * Copyright (c) 2022 Meta-Sonic
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 */
#pragma once

#include <algorithm>
#include <cctype>
#include <cmath>
#include <cstring>
#include <exception>
#include <fstream>
#include <functional>
#include <iomanip>
#include <iostream>
#include <limits>
#include <locale>
#include <map>
#include <numeric>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

#ifndef NANO_NAMESPACE
  #define NANO_NAMESPACE nano
#endif

#ifdef _MSC_VER
  #define NANO_TEST_MSVC_PRAGMA(X) __pragma(X)
#else
  #define NANO_TEST_MSVC_PRAGMA(X)
#endif

#ifdef __clang__
  #define NANO_TEST_CLANG_PRAGMA(X) _Pragma(X)
#else
  #define NANO_TEST_CLANG_PRAGMA(X)
#endif

#define NANO_TEST_MSVC_DIAGNOSTIC_PUSH() NANO_TEST_MSVC_PRAGMA(warning(push))
#define NANO_TEST_MSVC_DIAGNOSTIC_POP() NANO_TEST_MSVC_PRAGMA(warning(pop))
#define NANO_TEST_MSVC_PUSH_WARNING(X) NANO_TEST_MSVC_DIAGNOSTIC_PUSH() NANO_TEST_MSVC_PRAGMA(warning(disable : X))
#define NANO_TEST_MSVC_POP_WARNING() NANO_TEST_MSVC_DIAGNOSTIC_POP()

#define NANO_TEST_CLANG_DIAGNOSTIC_PUSH() NANO_TEST_CLANG_PRAGMA("clang diagnostic push")
#define NANO_TEST_CLANG_DIAGNOSTIC_POP() NANO_TEST_CLANG_PRAGMA("clang diagnostic pop")
#define NANO_TEST_CLANG_DIAGNOSTIC(TYPE, X) NANO_TEST_CLANG_PRAGMA(NANO_TEST_STRINGIFY(clang diagnostic TYPE X))

#define NANO_TEST_CLANG_PUSH_WARNING(X)                                                                                \
  NANO_TEST_CLANG_DIAGNOSTIC_PUSH() NANO_TEST_CLANG_PRAGMA(NANO_TEST_STRINGIFY(clang diagnostic ignored X))

#define NANO_TEST_CLANG_POP_WARNING() NANO_TEST_CLANG_DIAGNOSTIC_POP()

#define NANO_TEST_CONCAT1(_X, _Y) _X##_Y
#define NANO_TEST_CONCAT(_X, _Y) NANO_TEST_CONCAT1(_X, _Y)

#define NANO_TEST_STRINGIFY(X) NANO_TEST_STR(X)
#define NANO_TEST_STR(X) #X

NANO_TEST_CLANG_DIAGNOSTIC_PUSH()
NANO_TEST_CLANG_DIAGNOSTIC(ignored, "-Wvariadic-macros")
NANO_TEST_CLANG_DIAGNOSTIC(ignored, "-Wc++98-compat-pedantic")

#define NANO_TEST_GET_NTH_ARG(_1, _2, _3, _4, NAME, ...) NAME

#define NANO_TEST_EXPAND(X) X

#define TEST_CASE(...)                                                                                                 \
  NANO_TEST_EXPAND(NANO_TEST_GET_NTH_ARG(                                                                              \
      __VA_ARGS__, NANO_TEST_CASE_4, NANO_TEST_CASE_3, NANO_TEST_CASE_2, NANO_TEST_CASE_1)(__VA_ARGS__))

#define NANO_TEST_CASE_2(Group, Name) NANO_TEST_CASE_IMPL(Group, Name, "", "", 0)
#define NANO_TEST_CASE_3(Group, Name, Desc) NANO_TEST_CASE_IMPL(Group, Name, Desc, "", 0)
#define NANO_TEST_CASE_4(Group, Name, Desc, flags) NANO_TEST_CASE_IMPL(Group, Name, Desc, "", flags)

NANO_TEST_CLANG_DIAGNOSTIC_POP()

///
#define NANO_TEST_MAIN()                                                                                               \
  int main(int argc, const char* argv[]) { return NANO_NAMESPACE::test::run(argc, argv); }

///
#define NANO_TEST_ABORT_ON_ERROR 1

///
#define NANO_TEST_ABORT() NANO_TEST_ABORT_IMPL()

// MARK: - Expects and Asserts -

/// Tests that A is true.
///
/// EXPECT_EQ(A, B) is preferred to EXPECT_TRUE(A == B), as the former tells you what
/// the actual value is when it fails, and similarly for the other comparisons.
#define EXPECT_TRUE(A) NANO_TEST_EXPECT_IMPL(#A, A)
#define ASSERT_TRUE(A) NANO_TEST_ASSERT_IMPL(#A, A)

/// Tests that A is false.
///
/// EXPECT_NE(A, B) is preferred to EXPECT_FALSE(A == B), as the former tells you what
/// the actual value is when it fails, and similarly for the other comparisons.
#define EXPECT_FALSE(A) NANO_TEST_EXPECT_IMPL(NANO_TEST_STRINGIFY(!(A)), !(A))
#define ASSERT_FALSE(A) NANO_TEST_ASSERT_IMPL(NANO_TEST_STRINGIFY(!(A)), !(A))

/// Tests that A == B.
#define EXPECT_EQ(A, B) NANO_TEST_EXPECT_IMPL(NANO_TEST_STRINGIFY(A == B), (A == B))
#define ASSERT_EQ(A, B) NANO_TEST_ASSERT_IMPL(NANO_TEST_STRINGIFY(A == B), (A == B))

/// Tests that A != B.
#define EXPECT_NE(A, B) NANO_TEST_EXPECT_IMPL(NANO_TEST_STRINGIFY(A != B), (A != B))
#define ASSERT_NE(A, B) NANO_TEST_ASSERT_IMPL(NANO_TEST_STRINGIFY(A != B), (A != B))

/// Tests that A < B.
#define EXPECT_LT(A, B) NANO_TEST_EXPECT_IMPL(NANO_TEST_STRINGIFY(A < B), (A < B))
#define ASSERT_LT(A, B) NANO_TEST_ASSERT_IMPL(NANO_TEST_STRINGIFY(A < B), (A < B))

/// Tests that A <= B.
#define EXPECT_LE(A, B) NANO_TEST_EXPECT_IMPL(NANO_TEST_STRINGIFY(A <= B), (A <= B))
#define ASSERT_LE(A, B) NANO_TEST_ASSERT_IMPL(NANO_TEST_STRINGIFY(A <= B), (A <= B))

/// Tests that A > B.
#define EXPECT_GT(A, B) NANO_TEST_EXPECT_IMPL(NANO_TEST_STRINGIFY(A > B), (A > B))
#define ASSERT_GT(A, B) NANO_TEST_ASSERT_IMPL(NANO_TEST_STRINGIFY(A > B), (A > B))

/// Tests that A >= B.
#define EXPECT_GE(A, B) NANO_TEST_EXPECT_IMPL(NANO_TEST_STRINGIFY(A >= B), (A >= B))
#define ASSERT_GE(A, B) NANO_TEST_ASSERT_IMPL(NANO_TEST_STRINGIFY(A >= B), (A >= B))

/// Tests that A is null.
#define EXPECT_NULL(A) NANO_TEST_EXPECT_IMPL(NANO_TEST_STRINGIFY(A == NANO_TEST_NULLPTR), (A == NANO_TEST_NULLPTR))
#define ASSERT_NULL(A) NANO_TEST_ASSERT_IMPL(NANO_TEST_STRINGIFY(A == NANO_TEST_NULLPTR), (A == NANO_TEST_NULLPTR))

/// Tests that A is not null.
#define EXPECT_NOT_NULL(A) NANO_TEST_EXPECT_IMPL(NANO_TEST_STRINGIFY(A != NANO_TEST_NULLPTR), (A != NANO_TEST_NULLPTR))
#define ASSERT_NOT_NULL(A) NANO_TEST_ASSERT_IMPL(NANO_TEST_STRINGIFY(A != NANO_TEST_NULLPTR), (A != NANO_TEST_NULLPTR))

///
#define EXPECT_FLOAT_EQ(A, B)                                                                                          \
  NANO_TEST_EXPECT_IMPL(NANO_TEST_STRINGIFY(A == B), NANO_NAMESPACE::test::is_approximately_equal(A, B))
#define ASSERT_FLOAT_EQ(A, B)                                                                                          \
  NANO_TEST_ASSERT_IMPL(NANO_TEST_STRINGIFY(A == B), NANO_NAMESPACE::test::is_approximately_equal(A, B))

///
#define EXPECT_FLOAT_NE(A, B)                                                                                          \
  NANO_TEST_EXPECT_IMPL(NANO_TEST_STRINGIFY(A != B), (!NANO_NAMESPACE::test::is_approximately_equal(A, B)))
#define ASSERT_FLOAT_NE(A, B)                                                                                          \
  NANO_TEST_ASSERT_IMPL(NANO_TEST_STRINGIFY(A != B), (!NANO_NAMESPACE::test::is_approximately_equal(A, B)))

/// Expect floating point compare with tolerance.
#define EXPECT_FLOAT_EQ_T(A, B, T)                                                                                     \
  NANO_TEST_EXPECT_IMPL(NANO_TEST_STRINGIFY(A == B), NANO_NAMESPACE::test::is_approximately_equal(A, B, T))
#define ASSERT_FLOAT_EQ_T(A, B, T)                                                                                     \
  NANO_TEST_ASSERT_IMPL(NANO_TEST_STRINGIFY(A == B), NANO_NAMESPACE::test::is_approximately_equal(A, B, T))

///
#define EXPECT_FLOAT_NE_T(A, B, T)                                                                                     \
  NANO_TEST_EXPECT_IMPL(NANO_TEST_STRINGIFY(A != B), (!NANO_NAMESPACE::test::is_approximately_equal(A, B, T)))
#define ASSERT_FLOAT_NE_T(A, B, T)                                                                                     \
  NANO_TEST_ASSERT_IMPL(NANO_TEST_STRINGIFY(A != B), (!NANO_NAMESPACE::test::is_approximately_equal(A, B, T)))

/// Tests that std::string(A) == std::string(B).
#define EXPECT_STR_EQ(A, B) NANO_TEST_EXPECT_IMPL(NANO_TEST_STRINGIFY(A == B), (std::string(A) == std::string(B)))
#define ASSERT_STR_EQ(A, B) NANO_TEST_ASSERT_IMPL(NANO_TEST_STRINGIFY(A == B), (std::string(A) == std::string(B)))

/// Tests that std::string(A) != std::string(B).
#define EXPECT_STR_NE(A, B) NANO_TEST_EXPECT_IMPL(NANO_TEST_STRINGIFY(A != B), (std::string(A) != std::string(B)))
#define ASSERT_STR_NE(A, B) NANO_TEST_ASSERT_IMPL(NANO_TEST_STRINGIFY(A != B), (std::string(A) != std::string(B)))

///
#define EXPECT_EXCEPTION(Expr, exception_type) NANO_TEST_EXPECT_EXCEPTION_IMPL(Expr, exception_type)
#define ASSERT_EXCEPTION(Expr, exception_type) NANO_TEST_ASSERT_EXCEPTION_IMPL(Expr, exception_type)

///
#define EXPECT_RANGE_EQ(A, B, Size)                                                                                    \
  NANO_TEST_EXPECT_RANGE_IMPL(NANO_TEST_STRINGIFY(A == B), A, B, Size, NANO_NAMESPACE::test::comp_eq)
#define ASSERT_RANGE_EQ(A, B, Size)                                                                                    \
  NANO_TEST_ASSERT_RANGE_IMPL(NANO_TEST_STRINGIFY(A == B), A, B, Size, NANO_NAMESPACE::test::comp_eq)

///
#define EXPECT_RANGE_NE(A, B, Size)                                                                                    \
  NANO_TEST_EXPECT_RANGE_IMPL(NANO_TEST_STRINGIFY(A != B), A, B, Size, NANO_NAMESPACE::test::comp_ne)
#define ASSERT_RANGE_NE(A, B, Size)                                                                                    \
  NANO_TEST_ASSERT_RANGE_IMPL(NANO_TEST_STRINGIFY(A != B), A, B, Size, NANO_NAMESPACE::test::comp_ne)

///
#define EXPECT_RANGE_LT(A, B, Size)                                                                                    \
  NANO_TEST_EXPECT_RANGE_IMPL(NANO_TEST_STRINGIFY(A < B), A, B, Size, NANO_NAMESPACE::test::comp_lt)
#define ASSERT_RANGE_LT(A, B, Size)                                                                                    \
  NANO_TEST_ASSERT_RANGE_IMPL(NANO_TEST_STRINGIFY(A < B), A, B, Size, NANO_NAMESPACE::test::comp_lt)

///
#define EXPECT_RANGE_LE(A, B, Size)                                                                                    \
  NANO_TEST_EXPECT_RANGE_IMPL(NANO_TEST_STRINGIFY(A <= B), A, B, Size, NANO_NAMESPACE::test::comp_le)
#define ASSERT_RANGE_LE(A, B, Size)                                                                                    \
  NANO_TEST_ASSERT_RANGE_IMPL(NANO_TEST_STRINGIFY(A <= B), A, B, Size, NANO_NAMESPACE::test::comp_le)

///
#define EXPECT_RANGE_GT(A, B, Size)                                                                                    \
  NANO_TEST_EXPECT_RANGE_IMPL(NANO_TEST_STRINGIFY(A > B), A, B, Size, NANO_NAMESPACE::test::comp_gt)
#define ASSERT_RANGE_GT(A, B, Size)                                                                                    \
  NANO_TEST_ASSERT_RANGE_IMPL(NANO_TEST_STRINGIFY(A > B), A, B, Size, NANO_NAMESPACE::test::comp_gt)

///
#define EXPECT_RANGE_GE(A, B, Size)                                                                                    \
  NANO_TEST_EXPECT_RANGE_IMPL(NANO_TEST_STRINGIFY(A >= B), A, B, Size, NANO_NAMESPACE::test::comp_ge)
#define ASSERT_RANGE_GE(A, B, Size)                                                                                    \
  NANO_TEST_ASSERT_RANGE_IMPL(NANO_TEST_STRINGIFY(A >= B), A, B, Size, NANO_NAMESPACE::test::comp_ge)

// MARK: - Macro implementations -

// C4514: unreferenced inline function has been removed.
// C5045: mitigation.
NANO_TEST_MSVC_PUSH_WARNING(4514 5045)

#ifdef _MSVC_LANG
  #define NANO_TEST_CPP_VERSION _MSVC_LANG
#elif defined(__cplusplus)
  #define NANO_TEST_CPP_VERSION __cplusplus
#else
  #error Unknown C++ version
#endif

#if NANO_TEST_CPP_VERSION >= 201703L
  #define NANO_TEST_INLINE_PREFIX inline

#elif NANO_TEST_CPP_VERSION >= 201103L
  #define NANO_TEST_INLINE_PREFIX static

#elif NANO_TEST_CPP_VERSION >= 199711L
  #define NANO_TEST_CPP_98

#else
  #error Unsupported cpp version
#endif

#ifdef NANO_TEST_CPP_98
  #include <ctime>
  #include <sstream>

  #define NANO_TEST_NULLPTR NULL
  #define NANO_TEST_INLINE_CONSTEXPR static
  #define NANO_TEST_NOEXCEPT throw()

  #ifdef _MSC_VER
    #define NANO_TEST_NORETURN __declspec(noreturn)
  #else
    #define NANO_TEST_NORETURN __attribute__((noreturn))
  #endif // _MSC_VER

  #define NANO_TEST_CONSTEXPR
  #define NANO_TEST_INLINE_VARIABLE static
  #define NANO_TEST_OVERRIDE
  #define NANO_TEST_RVALUE_REF(X) const X&
  #define NANO_TEST_MOVE(X) X
  #define NANO_TEST_DEFAULT()                                                                                          \
    {}

  #define NANO_TEST_TO_STRING(X) NANO_NAMESPACE::test::to_string(X)

NANO_TEST_CLANG_DIAGNOSTIC_PUSH()
NANO_TEST_CLANG_DIAGNOSTIC(ignored, "-Wunknown-warning-option")
NANO_TEST_CLANG_DIAGNOSTIC(ignored, "-Wsuggest-destructor-override")
NANO_TEST_CLANG_DIAGNOSTIC(ignored, "-Wsuggest-override")

#else
  #include <chrono>
  #include <type_traits>

  #define NANO_TEST_INLINE_CONSTEXPR NANO_TEST_INLINE_PREFIX constexpr
  #define NANO_TEST_INLINE_VARIABLE NANO_TEST_INLINE_PREFIX
  #define NANO_TEST_NULLPTR nullptr
  #define NANO_TEST_OVERRIDE override
  #define NANO_TEST_NOEXCEPT noexcept
  #define NANO_TEST_NORETURN [[noreturn]]
  #define NANO_TEST_CONSTEXPR constexpr
  #define NANO_TEST_RVALUE_REF(X) X&&
  #define NANO_TEST_MOVE(X) std::move(X)
  #define NANO_TEST_DEFAULT() = default;
  #define NANO_TEST_TO_STRING(X) std::to_string(X)
#endif

namespace NANO_NAMESPACE {
namespace test {
  template <class T>
  inline std::string to_string(T __val) {
    std::ostringstream stream;
    stream << __val;
    return stream.str();
  }
} // namespace test.
} // namespace NANO_NAMESPACE.

namespace argparse {
namespace detail {
  static inline std::string _ltrim_dash_copy(std::string s) {
    for (std::string::iterator it = s.begin(); it != s.end(); ++it) {
      if (*it != '-') {
        s.erase(s.begin(), it);
        return s;
      }
    }

    return s;
  }

  static inline bool is_number(const std::string& arg) {
    char* end;
    std::strtod(arg.c_str(), &end);
    return end != arg.c_str();
  }

} // namespace detail

class argument {
public:
  enum position { LAST = -1, DONT_CARE = -2 };
  enum count { ANY = -1 };

  inline argument& name(NANO_TEST_RVALUE_REF(std::string) name) {
    _names.push_back(NANO_TEST_MOVE(name));
    return *this;
  }

  inline argument& names(NANO_TEST_RVALUE_REF(std::string) name1, NANO_TEST_RVALUE_REF(std::string) name2) {
    _names.push_back(NANO_TEST_MOVE(name1));
    _names.push_back(NANO_TEST_MOVE(name2));
    return *this;
  }

  inline argument& names(const std::vector<std::string>& names) {
    _names.insert(_names.end(), names.begin(), names.end());
    return *this;
  }

  inline argument& description(NANO_TEST_RVALUE_REF(std::string) description) NANO_TEST_NOEXCEPT {
    _desc = NANO_TEST_MOVE(description);
    return *this;
  }

  inline argument& required(bool req) NANO_TEST_NOEXCEPT {
    _required = req;
    return *this;
  }

  inline argument& position(int position) NANO_TEST_NOEXCEPT {
    // Argument zero is the name of the executable.
    _position = position + static_cast<int>(position != LAST);
    return *this;
  }

  inline argument& count(int count) NANO_TEST_NOEXCEPT {
    _count = count;
    return *this;
  }

  inline bool found() const NANO_TEST_NOEXCEPT { return _found; }

  inline const std::vector<std::string>& get_values() const NANO_TEST_NOEXCEPT { return _values; }

  inline std::string get_string() const {
    std::ostringstream ss;
    std::vector<std::string>::const_iterator begin = _values.begin();

    if (begin != _values.end()) {
      ss << *begin++;
    }
    while (begin != _values.end()) {
      ss << ' ';
      ss << *begin++;
    }
    return ss.str();
  }

private:
  inline argument(const std::string& name, const std::string& desc, bool required = false)
      : _desc(desc)
      , _position(DONT_CARE)
      , _count(ANY)
      , _index(-1)
      , _found(false)
      , _required(required)
      , _reserved(0) {
    _names.push_back(name);
  }

  inline argument()
      : _position(DONT_CARE)
      , _count(ANY)
      , _index(-1)
      , _found(false)
      , _required(false)
      , _reserved(0) {
    (void)_reserved;
  }

  friend class argument_parser;

  std::vector<std::string> _names;
  std::vector<std::string> _values;
  std::string _desc;

  int _position;
  int _count;
  int _index;

  bool _found;
  bool _required;
  short _reserved;
};

class result {
public:
  inline result() {}
  inline result(std::string err) NANO_TEST_NOEXCEPT : _what(err) {}

  inline operator bool() const { return !_what.empty(); }

  inline friend std::ostream& operator<<(std::ostream& os, const result& dt);

  const std::string& what() const { return _what; }

private:
  std::string _what;
};

NANO_TEST_CLANG_PUSH_WARNING("-Wpadded")
class argument_parser {
public:
  inline argument_parser(const std::string& bin, const std::string& desc)
      : _bin(bin)
      , _desc(desc)
      , _current(-1)
      , _help_enabled(false) {}

  inline argument& add_argument() {
    _arguments.push_back(argument());
    _arguments.back()._index = static_cast<int>(_arguments.size()) - 1;
    return _arguments.back();
  }

  inline argument& add_argument(
      const std::string& name, const std::string& long_name, const std::string& desc, const bool required = false) {
    _arguments.push_back(argument(name, desc, required));
    _arguments.back()._names.push_back(long_name);
    _arguments.back()._index = static_cast<int>(_arguments.size()) - 1;
    return _arguments.back();
  }

  inline argument& add_argument(const std::string& name, const std::string& desc, const bool required = false) {
    _arguments.push_back(argument(name, desc, required));
    _arguments.back()._index = static_cast<int>(_arguments.size()) - 1;
    return _arguments.back();
  }

  inline void print_help(size_t count = 0, size_t page = 0) {
    if (page * count > _arguments.size()) {
      return;
    }
    if (page == 0) {
      std::cout << "Usage: " << _bin;
      if (_positional_arguments.empty()) {
        std::cout << " [options...]" << std::endl;
      }
      else {
        int current = 1;

        for (std::map<int, int>::const_iterator v = _positional_arguments.begin(); v != _positional_arguments.end();
             ++v) {
          if (v->first != argument::LAST) {
            for (; current < v->first; current++) {
              std::cout << " [" << current << "]";
            }
            std::cout << " [" << detail::_ltrim_dash_copy(_arguments[static_cast<size_t>(v->second)]._names[0]) << "]";
          }
        }

        std::map<int, int>::const_iterator it = _positional_arguments.find(argument::LAST);
        if (it == _positional_arguments.end()) {
          std::cout << " [options...]";
        }
        else {
          std::cout << " [options...] ["
                    << detail::_ltrim_dash_copy(_arguments[static_cast<size_t>(it->second)]._names[0]) << "]";
        }
        std::cout << std::endl;
      }

      std::cout << "Options:" << std::endl;
    }

    if (count == 0) {
      page = 0;
      count = _arguments.size();
    }

    for (size_t i = page * count; i < std::min<size_t>(page * count + count, _arguments.size()); i++) {
      argument& a = _arguments[i];
      std::string name = a._names[0];

      for (size_t n = 1; n < a._names.size(); ++n) {
        name.append(", " + a._names[n]);
      }

      std::cout << "    " << std::setw(23) << std::left << name << std::setw(23) << a._desc;
      if (a._required) {
        std::cout << " (Required)";
      }

      std::cout << std::endl;
    }
  }

  inline result parse(int argc, const char* argv[]) {

    if (argc > 1) {

      // Build name map.
      for (std::vector<argument>::const_iterator a = _arguments.begin(); a != _arguments.end(); ++a) {
        for (std::vector<std::string>::const_iterator n = a->_names.begin(); n != a->_names.end(); ++n) {
          std::string name = detail::_ltrim_dash_copy(*n);

          if (_name_map.find(name) != _name_map.end()) {
            return result("Duplicate of argument name: " + *n);
          }

          _name_map[name] = a->_index;
        }

        if (a->_position >= 0 || a->_position == argument::LAST) {
          _positional_arguments[a->_position] = a->_index;
        }
      }

      // Parse.
      std::string current_arg;
      size_t arg_len;

      for (int argv_index = 1; argv_index < argc; ++argv_index) {
        current_arg = std::string(argv[argv_index]);
        arg_len = current_arg.length();

        if (arg_len == 0) {
          continue;
        }

        if (_help_enabled && (current_arg == "-h" || current_arg == "--help")) {
          _arguments[static_cast<size_t>(_name_map["help"])]._found = true;
        }
        else if (argv_index == argc - 1 && _positional_arguments.find(argument::LAST) != _positional_arguments.end()) {

          result err = _end_argument();

          result b = err;
          err = _add_value(current_arg, argument::LAST);

          if (b) {
            return b;
          }

          if (err) {
            return err;
          }
        }

        // Ignores the case if the arg is just a '-'.
        else if (arg_len >= 2 && !detail::is_number(current_arg)) {

          // Look for -a (short) or --arg (long) args.
          if (current_arg[0] == '-') {

            if (result err = _end_argument()) {
              return err;
            }

            // Look for --arg (long) args.
            if (current_arg[1] == '-') {

              if (result err = _begin_argument(current_arg.substr(2), true, argv_index)) {
                return err;
              }
            }

            // Short args.
            else if (result err = _begin_argument(current_arg.substr(1), false, argv_index)) {
              return err;
            }
          }

          // Argument value.
          else if (result err = _add_value(current_arg, argv_index)) {
            return err;
          }
        }

        // Argument value.
        else if (result err = _add_value(current_arg, argv_index)) {
          return err;
        }
      }
    }

    if (_help_enabled && exists("help")) {
      return result();
    }

    if (result err = _end_argument()) {
      return err;
    }

    for (std::map<int, int>::const_iterator p = _positional_arguments.begin(); p != _positional_arguments.end(); ++p) {
      const argument& a = _arguments[static_cast<size_t>(p->second)];
      if (a._values.size() > 0 && a._values[0][0] == '-') {
        std::string name = detail::_ltrim_dash_copy(a._values[0]);

        if (_name_map.find(name) != _name_map.end()) {
          if (a._position == argument::LAST) {
            return result("Poisitional argument expected at the end, but argument " + a._values[0] + " found instead");
          }
          else {
            return result("Poisitional argument expected in position " + NANO_TEST_TO_STRING(a._position)
                + ", but argument " + a._values[0] + " found instead");
          }
        }
      }
    }

    for (std::vector<argument>::const_iterator a = _arguments.begin(); a != _arguments.end(); ++a) {
      if (a->_required && !a->_found) {
        return result("Required argument not found: " + a->_names[0]);
      }

      if (a->_position >= 0 && argc >= a->_position && !a->_found) {
        return result("Argument " + a->_names[0] + " expected in position " + NANO_TEST_TO_STRING(a->_position));
      }
    }

    return result();
  }

  inline void enable_help() {
    add_argument("-h", "--help", "Shows this page", false);
    _help_enabled = true;
  }

  inline bool exists(const std::string& name) const {
    std::string n = detail::_ltrim_dash_copy(name);
    std::map<std::string, int>::const_iterator it = _name_map.find(n);
    return it == _name_map.end() ? false : _arguments[static_cast<size_t>(it->second)]._found;
  }

  inline const argument* get_argument(const std::string& name) const {
    std::map<std::string, int>::const_iterator t = _name_map.find(name);
    if (t == _name_map.end()) {
      return NANO_TEST_NULLPTR;
    }

    const argument* arg = &_arguments[static_cast<size_t>(t->second)];
    return arg->_found ? arg : NANO_TEST_NULLPTR;
  }

private:
  inline result _begin_argument(const std::string& arg, bool longarg, int position) {

    std::map<int, int>::iterator it = _positional_arguments.find(position);
    if (it != _positional_arguments.end()) {
      result err = _end_argument();
      argument& a = _arguments[static_cast<size_t>(it->second)];
      a._values.push_back((longarg ? "--" : "-") + arg);
      a._found = true;
      return err;
    }

    if (_current != -1) {
      return result("Current argument left open");
    }

    size_t name_end;
    for (name_end = 0; name_end < arg.length(); ++name_end) {
      if (std::ispunct(static_cast<int>(arg[name_end]))) {
        break;
      }
    }

    std::string arg_name = arg.substr(0, name_end);

    if (longarg) {
      int equal_pos = -1;

      // _find_equal.
      for (size_t i = 0; i < arg.length(); ++i) {
        // if find graph symbol before equal, end search
        // i.e. don't accept --asd)f=0 arguments
        // but allow --asd_f and --asd-f arguments
        if (std::ispunct(static_cast<int>(arg[i]))) {
          if (arg[i] == '=') {
            equal_pos = static_cast<int>(i);
            break;
          }
          else if (arg[i] == '_' || arg[i] == '-') {
            continue;
          }

          equal_pos = -1;
          break;
        }
      }

      std::map<std::string, int>::iterator nmf = _name_map.find(arg_name);
      if (nmf == _name_map.end()) {
        return result("Unrecognized command line option '" + arg_name + "'");
      }

      _current = nmf->second;
      _arguments[static_cast<size_t>(nmf->second)]._found = true;

      // Malformed argument.
      if (equal_pos == 0 || (equal_pos < 0 && arg_name.length() < arg.length())) {
        return result("Malformed argument: " + arg);
      }
      else if (equal_pos > 0) {
        _add_value(arg.substr(name_end + 1), position);
      }
    }
    else {
      if (arg_name.length() == 1) {
        return _begin_argument(arg, true, position);
      }
      else {
        for (std::string::const_iterator c = arg_name.begin(); c != arg_name.end(); ++c) {

          if (result r = _begin_argument(std::string(1, *c), true, position)) {
            return r;
          }

          if (result r = _end_argument()) {
            return r;
          }
        }
      }
    }

    return result();
  }

  inline result _add_value(const std::string& value, int location) {

    if (_current < 0) {
      std::map<int, int>::iterator it = _positional_arguments.find(location);
      if (it != _positional_arguments.end()) {
        argument& a = _arguments[static_cast<size_t>(it->second)];
        a._values.push_back(value);
        a._found = true;
      }

      // TODO
      return result();
    }

    argument& a = _arguments[static_cast<size_t>(_current)];

    if (a._count >= 0 && static_cast<int>(a._values.size()) >= a._count) {

      if (result err = _end_argument()) {
        return err;
      }

      std::map<int, int>::iterator it = _positional_arguments.find(location);
      if (it != _positional_arguments.end()) {
        argument& pa = _arguments[static_cast<size_t>(it->second)];
        pa._values.push_back(value);
        pa._found = true;
      }

      // TODO
      return result();
    }

    a._values.push_back(value);

    if (a._count >= 0 && static_cast<int>(a._values.size()) >= a._count) {
      return _end_argument();
    }

    return result();
  }

  inline result _end_argument() {
    if (_current < 0) {
      return result();
    }

    argument& a = _arguments[static_cast<size_t>(_current)];
    _current = -1;

    const int vsize = static_cast<int>(a._values.size());

    if (vsize < a._count) {
      return result("Too few arguments given for " + a._names[0]);
    }

    if (a._count >= 0 && vsize > a._count) {
      return result("Too many arguments given for " + a._names[0]);
    }

    return result();
  }

  std::string _bin;
  std::string _desc;
  std::vector<argument> _arguments;
  std::map<int, int> _positional_arguments;
  std::map<std::string, int> _name_map;
  int _current;
  bool _help_enabled;
};
NANO_TEST_CLANG_POP_WARNING() // -Wpadded

inline std::ostream& operator<<(std::ostream& os, const result& r) {
  os << r.what();
  return os;
}
} // namespace argparse

namespace NANO_NAMESPACE {
namespace test {

  // MARK: - Exceptions -

  template <class = void>
  class test_exception : public std::exception {
  public:
    virtual ~test_exception() NANO_TEST_NOEXCEPT NANO_TEST_OVERRIDE NANO_TEST_DEFAULT()
  };

  template <class = void>
  class failed_expect_exception : public test_exception<> {
  public:
    inline failed_expect_exception(const char* expr_str, const char* file, int line)
        : m_error_str(create_message(expr_str, file, line)) {}

    virtual ~failed_expect_exception() NANO_TEST_NOEXCEPT NANO_TEST_OVERRIDE NANO_TEST_DEFAULT()

        virtual const char* what() const NANO_TEST_NOEXCEPT NANO_TEST_OVERRIDE {
      return m_error_str.c_str();
    }

  private:
    std::string m_error_str;

    static inline std::string create_message(const char* expr_str, const char* file, int line) {
      std::stringstream ss;
      ss << "    - Assert failed\n      expected : " << expr_str << "\n      source   : " << file
         << "\n      line     : " << line << "\n";
      return ss.str();
    }
  };

  template <class = void>
  class failed_exception : public test_exception<> {
  public:
    inline failed_exception(const char* except_str, const char* expected_str, const char* file, int line)
        : m_error_str(create_message(except_str, expected_str, file, line)) {}

    virtual ~failed_exception() NANO_TEST_NOEXCEPT NANO_TEST_OVERRIDE NANO_TEST_DEFAULT()

        inline virtual const char* what() const NANO_TEST_NOEXCEPT NANO_TEST_OVERRIDE {
      return m_error_str.c_str();
    }

  private:
    std::string m_error_str;

    static inline std::string create_message(
        const char* except_str, const char* expected_str, const char* file, int line) {
      std::stringstream ss;
      ss << "    - Assert exception failed\n      expected : " << expected_str << "\n      got      : " << except_str
         << "\n      source   : " << file << "\n      line     : " << line << "\n";

      return ss.str();
    }
  };

  inline void custom_assert(const char* expr_str, bool expr, const char* file, int line) {
    if (expr) {
      return;
    }
    throw NANO_NAMESPACE::test::failed_expect_exception<>(expr_str, file, line);
  }

  NANO_TEST_NORETURN inline void custom_exception(const char* expr_str, bool is_caught, const char* file, int line) {
    throw NANO_NAMESPACE::test::failed_exception<>(
        is_caught ? "unexpected exception" : "no exception", expr_str, file, line);
  }

  namespace detail {
    template <typename T1, typename T2>
    struct float_common_return {
#ifdef NANO_TEST_CPP_98
      typedef double type;
#else
      typedef typename std::conditional<std::is_integral<typename std::common_type<T1, T2>::type>::value, float,
          typename std::common_type<T1, T2>::type>::type type;
#endif // NANO_TEST_CPP_98
    };

#ifdef NANO_TEST_CPP_98
    template <class StartT>
    inline NANO_TEST_CONSTEXPR double get_us_count(const StartT& start) {
      return (static_cast<double>(std::clock()) - static_cast<double>(start)) * (1000000.0 / CLOCKS_PER_SEC);
    }
#else
    template <class StartT>
    inline NANO_TEST_CONSTEXPR std::chrono::microseconds::rep get_us_count(const StartT& start) {
      return std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - start)
          .count();
    }
#endif

    NANO_TEST_INLINE_CONSTEXPR const char* kOk = "[       OK ]";
    NANO_TEST_INLINE_CONSTEXPR const char* kFailed = "[  FAILED  ]";

    NANO_TEST_INLINE_CONSTEXPR const char* kTest = "test";
    NANO_TEST_INLINE_CONSTEXPR const char* kTests = "tests";
  } // namespace detail

  // MARK: - Test case -

  typedef void (*test_function)();

  struct test_item {
    inline test_item(const std::string& _name, const std::string& _desc, test_function _fct, long _flags)
        : name(_name)
        , desc(_desc)
        , fct(_fct)
        , flags(_flags) {}

    std::string name;
    std::string desc;
    test_function fct;
    long flags;
  };

  // MARK: - Test check result -

  struct check_result {
    inline check_result(const char* _group, const test_item* _item, const char* _expr, const char* _file,
        std::size_t _line, std::size_t _end_time, bool _success)
        : group(_group)
        , item(_item)
        , expr(_expr)
        , file(_file)
        , line(_line)
        , end_time(_end_time)
        , success(_success) {}

    const char* group;
    const test_item* item;
    const char* expr;

    const char* file;
    std::size_t line;
    std::size_t end_time;
    bool success;
    char reserved[7];
  };

  template <typename Comp, typename T1, typename T2>
  inline bool compare_range(const T1* a, const T2* b, std::size_t size) {
    for (std::size_t i = 0; i < size; i++) {
      if (!Comp()(a[i], b[i])) {
        return false;
      }
    }

    return true;
  }

  // MARK: - Tests manager -

  class manager {
  public:
    typedef std::vector<test_item> test_vector;
    typedef std::map<std::string, test_vector> test_map;

    struct state {
      state()
          : current_item(NANO_TEST_NULLPTR)
          , passed_count(0)
          , failed_count(0)
          , total_tests(0)
          , check_count(0)
          , failed_check_count(0)
          , results(NANO_TEST_NULLPTR)
          , current_test_failed(false)
          , should_stop(false)

      {}

      const test_item* current_item;
      std::size_t passed_count;
      std::size_t failed_count;
      std::size_t total_tests;
      std::size_t check_count;
      std::size_t failed_check_count;

#ifdef NANO_TEST_CPP_98
      struct clock {
        static inline double now() { return static_cast<double>(std::clock()); }
      };
      double launch_start_time;
      double group_start_time;
      double test_start_time;
#else
      typedef std::chrono::high_resolution_clock clock;

      clock::time_point launch_start_time;
      clock::time_point group_start_time;
      clock::time_point test_start_time;
#endif
      const char* current_group;
      const char* current_test;

      std::vector<check_result>* results;

      bool current_test_failed;
      bool should_stop;
      char reserved[6];

      inline void add_check(bool success, const char* expr, const char* file, std::size_t line) {
        if (results) {
          results->push_back(check_result(current_group, current_item, expr, file, line,
              static_cast<std::size_t>(detail::get_us_count(test_start_time)), success));
        }
      }

      inline void start_group(const test_map::value_type& g) {
        current_group = g.first.c_str();

        group_start_time = state::clock::now();
        std::cout << "[----------] " << g.second.size() << " " << test(g.second.size()) << " from group '" << g.first
                  << "'" << std::endl;
      }

      inline void end_group(const test_map::value_type& g) {
        std::cout << "[----------] group '" << g.first << "' (" << group_us() << " us). \n\n";
      }

      inline void run_test(const test_item& t) {
        current_item = &t;
        current_test = t.name.c_str();
        current_test_failed = false;
        check_count = 0;
        failed_check_count = 0;
        test_start_time = state::clock::now();

        std::cout << "[ RUN      ] > test case " << t.name << " : " << t.desc << std::endl;

        try {
          t.fct();
        } catch (const NANO_NAMESPACE::test::test_exception<>& e) {
          failed_check_count++;
          current_test_failed = true;
          std::cout << e.what();
        } catch (const std::exception& e) {
          // Other errors
          throw e;
        }

        if (current_test_failed) {
          failed_count++;
        }
        else {
          passed_count++;
        }

        report(!current_test_failed);

        if (current_test_failed) {
          if (t.flags & NANO_TEST_ABORT_ON_ERROR) {
            should_stop = true;
          }
        }
      }

      inline void report(bool passed) {
        if (passed) {
          std::cout << detail::kOk << " < test case " << current_test << " (" << check_count << " checks) ("
                    << test_us() << " us)" << std::endl;
        }
        else {
          std::cout << detail::kFailed << " < test case " << current_test << " (" << (check_count - failed_check_count)
                    << '/' << check_count << " checks) (" << test_us() << " us)" << std::endl;
        }
      }

#ifdef NANO_TEST_CPP_98
      inline double test_us() const { return detail::get_us_count(test_start_time); }
      inline double group_us() const { return detail::get_us_count(group_start_time); }
      inline double launch_us() const { return detail::get_us_count(launch_start_time); }
#else
      inline std::chrono::microseconds::rep test_us() const { return detail::get_us_count(test_start_time); }

      inline std::chrono::microseconds::rep group_us() const { return detail::get_us_count(group_start_time); }

      inline std::chrono::microseconds::rep launch_us() const { return detail::get_us_count(launch_start_time); }
#endif

      inline static NANO_TEST_CONSTEXPR const char* test(std::size_t count) {
        return count <= 1 ? detail::kTest : detail::kTests;
      }

      inline static NANO_TEST_CONSTEXPR const char* group(std::size_t count) { return count <= 1 ? "group" : "groups"; }
    };

    static inline manager& get_instance() {
      NANO_TEST_CLANG_PUSH_WARNING("-Wexit-time-destructors")
      static manager tm;
      return tm;
      NANO_TEST_CLANG_POP_WARNING()
    }

    static inline state& state() { return get_instance().m_state; }

    static inline void add_test(
        const char* group, const char* name, const char* desc, const char* opts, long flags, test_function fct) {
      (void)opts;
      test_vector& vec = get_instance().m_tests[group];
      test_item item(name, desc, fct, flags);
      vec.insert(std::upper_bound(vec.begin(), vec.end(), item, item_comparator()), NANO_TEST_MOVE(item));
    }

    inline static int run(int argc, const char* argv[]);
    inline static int run(int argc, const char* argv[], std::vector<check_result>& results);

  private:
    inline manager() {}

    test_map m_tests;
    struct state m_state;

    inline int run_impl(int argc, const char* argv[], std::vector<check_result>* results);

    struct item_comparator {
      inline bool operator()(const test_item& a, const test_item& b) const { return a.name < b.name; }
    };
  };

  // MARK: - Inline implementations -

#ifdef NANO_TEST_CPP_98
  template <typename T1, typename T2, typename T3>
  inline bool is_approximately_equal(T1 a, T2 b, T3 tolerance) {
    typedef typename detail::float_common_return<T1, T2>::type ftype;

    const ftype fa = static_cast<ftype>(a);
    const ftype fb = static_cast<ftype>(b);
    const ftype t = static_cast<ftype>(tolerance);
    return (std::abs(fa - fb) <= t) || (std::abs(fa - fb) < (std::max(std::abs(fa), std::abs(fb)) * t));
  }

  template <typename T1, typename T2>
  inline bool is_approximately_equal(T1 a, T2 b, double tolerance = std::numeric_limits<double>::epsilon()) {
    typedef typename detail::float_common_return<T1, T2>::type ftype;

    const ftype fa = static_cast<ftype>(a);
    const ftype fb = static_cast<ftype>(b);
    const ftype t = static_cast<ftype>(tolerance);
    return (std::abs(fa - fb) <= t) || (std::abs(fa - fb) < (std::max(std::abs(fa), std::abs(fb)) * t));
  }

#else
  template <typename T1, typename T2>
  inline bool is_approximately_equal(T1 a, T2 b,
      typename detail::float_common_return<T1, T2>::type tolerance
      = std::numeric_limits<typename detail::float_common_return<T1, T2>::type /**/>::epsilon()) {
    typedef typename detail::float_common_return<T1, T2>::type ftype;

    const ftype fa = static_cast<ftype>(a);
    const ftype fb = static_cast<ftype>(b);
    return (std::abs(fa - fb) <= tolerance) || (std::abs(fa - fb) < (std::max(std::abs(fa), std::abs(fb)) * tolerance));
  }
#endif

#define NANO_TEST_DECL_COMP(name, comp)                                                                                \
  struct comp_##name {                                                                                                 \
    template <typename T1, typename T2>                                                                                \
    inline NANO_TEST_CONSTEXPR bool operator()(const T1& a, const T2& b) const {                                       \
      return a comp b;                                                                                                 \
    }                                                                                                                  \
  }

  NANO_TEST_DECL_COMP(eq, ==);
  NANO_TEST_DECL_COMP(ne, !=);
  NANO_TEST_DECL_COMP(lt, <);
  NANO_TEST_DECL_COMP(le, <=);
  NANO_TEST_DECL_COMP(gt, >);
  NANO_TEST_DECL_COMP(ge, >=);

#undef NANO_TEST_DECL_COMP

  int manager::run(int argc, const char* argv[]) { return get_instance().run_impl(argc, argv, NANO_TEST_NULLPTR); }

  int manager::run(int argc, const char* argv[], std::vector<check_result>& results) {
    return get_instance().run_impl(argc, argv, &results);
  }

  int manager::run_impl(int argc, const char* argv[], std::vector<check_result>* results) {

    argparse::argument_parser parser("utest", "Unit tests runner");
    parser.add_argument("-v", "--verbose", "verbose", false).count(0);
    parser.add_argument("-g", "--groups", "group tests to run", false);
    parser.enable_help();

    argparse::result err = parser.parse(argc, argv);
    if (err) {
      std::cout << err << std::endl;
      return -1;
    }

    if (parser.exists("help")) {
      parser.print_help();
      return 0;
    }

    const std::vector<std::string>* groups_ptr = NANO_TEST_NULLPTR;
    const argparse::argument* groups_arg = parser.get_argument("groups");
    if (groups_arg) {
      const std::vector<std::string>& groups = groups_arg->get_values();
      groups_ptr = &groups;
    }
    //    bool hasGroups = parser.get_argument("groups")->get_values()

    if (results) {
      m_state.results = results;
    }

    m_state.passed_count = 0;
    m_state.failed_count = 0;
    m_state.total_tests = 0;
    m_state.should_stop = false;

    std::set<std::string> group_map;

    if (groups_ptr) {
      for (std::size_t i = 0; i < groups_ptr->size(); i++) {
        group_map.insert(groups_ptr->operator[](i));
      }

      for (test_map::const_iterator g = m_tests.begin(); g != m_tests.end(); ++g) {
        if (group_map.find(g->first) != group_map.end()) {
          m_state.total_tests += g->second.size();
        }
      }
    }
    else {
      for (test_map::const_iterator g = m_tests.begin(); g != m_tests.end(); ++g) {
        m_state.total_tests += g->second.size();
      }
    }

    std::cout << "[==========] Running " << m_state.total_tests << " " << state::test(m_state.total_tests) << " from "
              << m_tests.size() << " test " << state::group(m_tests.size()) << ".\n\n";

    m_state.launch_start_time = state::clock::now();

    for (test_map::const_iterator g = m_tests.begin(); g != m_tests.end(); ++g) {
      if (!group_map.empty() && group_map.find(g->first) == group_map.end()) {
        continue;
      }

      m_state.start_group(*g);

      for (test_vector::const_iterator t = g->second.begin(); t != g->second.end(); ++t) {
        m_state.run_test(*t);

        if (m_state.should_stop) {
          break;
        }
      }

      m_state.end_group(*g);

      if (m_state.should_stop) {
        std::cout << "\n[==========] Stopped in test case '" << m_state.current_test << "' from '"
                  << m_state.current_group << "' group.\n\n"
                  << std::endl;

        break;
      }
    }

    std::cout << "[==========] " << m_state.total_tests << " " << state::test(m_state.total_tests) << " from "
              << m_tests.size() << " test " << state::group(m_tests.size()) << " (" << m_state.launch_us() << " us)."
              << std::endl;

    std::cout << "[  PASSED  ] " << m_state.passed_count << " " << state::test(m_state.passed_count) << std::endl;

    if (m_state.failed_count) {
      std::cout << "[  FAILED  ] " << m_state.failed_count << " " << state::test(m_state.failed_count) << std::endl;
    }

    return static_cast<int>(m_state.failed_count);
  }

  inline int run(int argc, const char* argv[]) { return manager::run(argc, argv); }

  inline int run(int argc, const char* argv[], std::vector<nano::test::check_result>& results) {
    return manager::run(argc, argv, results);
  }
} // namespace test.
} // namespace NANO_NAMESPACE.

#define NANO_TEST_EXPECT_IMPL(S, Expr)                                                                                 \
  do {                                                                                                                 \
    struct NANO_NAMESPACE::test::manager::state& __state = NANO_NAMESPACE::test::manager::state();                     \
    NANO_TEST_MSVC_PUSH_WARNING(4127)                                                                                  \
    try {                                                                                                              \
      __state.check_count++;                                                                                           \
      if (!(Expr)) {                                                                                                   \
        __state.current_test_failed = true;                                                                            \
        __state.failed_check_count++;                                                                                  \
        __state.add_check(false, S, __FILE__, __LINE__);                                                               \
        std::cout << "    > Check failed\n      expected : " << S << "\n      source   : " << __FILE__                 \
                  << "\n      line     : " << __LINE__ << "\n";                                                        \
      }                                                                                                                \
      else {                                                                                                           \
        __state.add_check(true, S, __FILE__, __LINE__);                                                                \
      }                                                                                                                \
    } catch (const std::exception& e) {                                                                                \
      throw e;                                                                                                         \
    }                                                                                                                  \
    NANO_TEST_MSVC_POP_WARNING()                                                                                       \
  } while (0)

#define NANO_TEST_EXPECT_EXCEPTION_IMPL(Expr, exception_type)                                                          \
  do {                                                                                                                 \
    struct NANO_NAMESPACE::test::manager::state& __state = NANO_NAMESPACE::test::manager::state();                     \
    int exception_caught = 0;                                                                                          \
    try {                                                                                                              \
      __state.check_count++;                                                                                           \
      (Expr);                                                                                                          \
    } catch (const exception_type&) {                                                                                  \
      exception_caught = 1;                                                                                            \
    } catch (...) {                                                                                                    \
      exception_caught = 2;                                                                                            \
    }                                                                                                                  \
                                                                                                                       \
    if (exception_caught != 1) {                                                                                       \
      __state.current_test_failed = true;                                                                              \
      __state.failed_check_count++;                                                                                    \
      std::cout << "    > Check exception failed\n      expected : " << NANO_TEST_STRINGIFY(exception_type)            \
                << "\n      got      : " << (exception_caught == 2 ? "unexpected exception" : "no exception")          \
                << "\n      source   : " << __FILE__ << "\n      line     : " << __LINE__ << "\n";                     \
    }                                                                                                                  \
  } while (0)

#define NANO_TEST_EXPECT_RANGE_IMPL(S, A, B, Size, Comp)                                                               \
  do {                                                                                                                 \
    NANO_TEST_MSVC_PUSH_WARNING(4127)                                                                                  \
    struct NANO_NAMESPACE::test::manager::state& __state = NANO_NAMESPACE::test::manager::state();                     \
    try {                                                                                                              \
      __state.check_count++;                                                                                           \
      if (!NANO_NAMESPACE::test::compare_range<Comp>(A, B, static_cast<std::size_t>(Size))) {                          \
        __state.current_test_failed = true;                                                                            \
        __state.failed_check_count++;                                                                                  \
        __state.add_check(false, S, __FILE__, __LINE__);                                                               \
        std::cout << "    > Check failed\n      expected : " << S << "\n      source   : " << __FILE__                 \
                  << "\n      line     : " << __LINE__ << "\n";                                                        \
      }                                                                                                                \
      else {                                                                                                           \
        __state.add_check(true, S, __FILE__, __LINE__);                                                                \
      }                                                                                                                \
    } catch (const std::exception& e) {                                                                                \
      throw e;                                                                                                         \
    }                                                                                                                  \
    NANO_TEST_MSVC_POP_WARNING()                                                                                       \
  } while (0)

#define NANO_TEST_ASSERT_IMPL(S, Expr)                                                                                 \
  NANO_NAMESPACE::test::manager::state().check_count++;                                                                \
  NANO_NAMESPACE::test::custom_assert(S, Expr, __FILE__, __LINE__)

#define NANO_TEST_ASSERT_RANGE_IMPL(S, A, B, Size, Comp)                                                               \
  NANO_NAMESPACE::test::manager::state().check_count++;                                                                \
  NANO_NAMESPACE::test::custom_assert(                                                                                 \
      S, NANO_NAMESPACE::test::compare_range<Comp>(A, B, static_cast<std::size_t>(Size)), __FILE__, __LINE__)

#define NANO_TEST_ASSERT_EXCEPTION_IMPL(Expr, exception_type)                                                          \
  do {                                                                                                                 \
    struct NANO_NAMESPACE::test::manager::state& __state = NANO_NAMESPACE::test::manager::state();                     \
    int exception_caught = 0;                                                                                          \
    try {                                                                                                              \
      __state.check_count++;                                                                                           \
      (Expr);                                                                                                          \
    } catch (const exception_type&) {                                                                                  \
      exception_caught = 1;                                                                                            \
    } catch (...) {                                                                                                    \
      exception_caught = 2;                                                                                            \
    }                                                                                                                  \
    if (exception_caught != 1) {                                                                                       \
      __state.current_test_failed = true;                                                                              \
      __state.failed_check_count++;                                                                                    \
      NANO_NAMESPACE::test::custom_exception(                                                                          \
          NANO_TEST_STRINGIFY(exception_type), exception_caught == 2, __FILE__, __LINE__);                             \
    }                                                                                                                  \
  } while (0)

#ifdef _MSC_VER
  #define NANO_TEST_CASE_IMPL(group, name, desc, opts, flags)                                                          \
    void name();                                                                                                       \
    namespace __unit_tests {                                                                                           \
      namespace {                                                                                                      \
        struct name##__TestRegistration {                                                                              \
          inline name##__TestRegistration() {                                                                          \
            NANO_NAMESPACE::test::manager::add_test(group, #name, desc, opts, flags, &name);                           \
          }                                                                                                            \
        };                                                                                                             \
        static name##__TestRegistration name##__testRegistration = name##__TestRegistration{};                         \
      } /* namespace */                                                                                                \
    } /* namespace __unit_tests */                                                                                     \
    void name()

#else
  #define NANO_TEST_CASE_IMPL(group, name, desc, opts, flags)                                                          \
    void name();                                                                                                       \
    namespace __unit_tests {                                                                                           \
      namespace {                                                                                                      \
        __attribute__((constructor)) static void name##__TestRegistration() {                                          \
          NANO_NAMESPACE::test::manager::add_test(group, #name, desc, opts, flags, &name);                             \
        }                                                                                                              \
      } /* namespace */                                                                                                \
    } /* namespace __unit_tests */                                                                                     \
    void name()

#endif

#define NANO_TEST_ABORT_IMPL() NANO_NAMESPACE::test::manager::state().should_stop = true;

NANO_TEST_MSVC_POP_WARNING() // 4514 5045

#ifdef NANO_TEST_CPP_98
NANO_TEST_CLANG_DIAGNOSTIC_POP()
#endif //
