#pragma once

#include <algorithm>
#include <chrono>
#include <cmath>
#include <exception>
#include <functional>
#include <iostream>
#include <limits>
#include <map>
#include <sstream>
#include <string>
#include <type_traits>
#include <vector>

#include <fstream>
#include <iomanip>

///
#define UTEST_MAIN()                                                                                                   \
  int main(int argc, const char* argv[]) { return utest::run(argc, argv); }

///
#define TEST_CASE(group, name, desc) UTEST_CASE_IMPL(group, name, desc)

// MARK: - Expects -

///
#define EXPECT_TRUE(Expr) EXPECT_IMPL(#Expr, Expr)

///
#define EXPECT_FALSE(Expr) EXPECT_IMPL(UTEST_STRINGIFY(!(Expr)), !(Expr))

///
#define EXPECT_EQ(A, B) EXPECT_IMPL(UTEST_STRINGIFY(A == B), (A == B))

///
#define EXPECT_NE(A, B) EXPECT_IMPL(UTEST_STRINGIFY(A != B), (A != B))

///
#define EXPECT_LT(A, B) EXPECT_IMPL(UTEST_STRINGIFY(A < B), (A < B))

///
#define EXPECT_LE(A, B) EXPECT_IMPL(UTEST_STRINGIFY(A <= B), (A <= B))

///
#define EXPECT_GT(A, B) EXPECT_IMPL(UTEST_STRINGIFY(A > B), (A > B))

///
#define EXPECT_GE(A, B) EXPECT_IMPL(UTEST_STRINGIFY(A >= B), (A >= B))

///
#define EXPECT_NOT_NULL(A) EXPECT_IMPL(UTEST_STRINGIFY(A != nullptr), (A != nullptr))

///
#define EXPECT_NULL(A) EXPECT_IMPL(UTEST_STRINGIFY(A == nullptr), (A == nullptr))

///
#define EXPECT_FLOAT_EQ(A, B) EXPECT_IMPL(UTEST_STRINGIFY(A == B), utest::is_approximately_equal(A, B))

///
#define EXPECT_FLOAT_NE(A, B) EXPECT_IMPL(UTEST_STRINGIFY(A != B), (!utest::is_approximately_equal(A, B)))

/// Expect floating point compare with tolerance.
#define EXPECT_FLOAT_EQ_T(A, B, T) EXPECT_IMPL(UTEST_STRINGIFY(A == B), utest::is_approximately_equal(A, B, T))

///
#define EXPECT_FLOAT_NE_T(A, B, T) EXPECT_IMPL(UTEST_STRINGIFY(A != B), (!utest::is_approximately_equal(A, B, T)))

///
#define EXPECT_STR_EQ(A, B) EXPECT_IMPL(UTEST_STRINGIFY(A == B), (std::string(A) == std::string(B)))

///
#define EXPECT_STR_NE(A, B) EXPECT_IMPL(UTEST_STRINGIFY(A != B), (std::string(A) != std::string(B)))

///
#define EXPECT_EXCEPTION(Expr, exception_type) EXPECT_EXCEPTION_IMPL(Expr, exception_type)

// MARK: - Asserts -

///
#define ASSERT_TRUE(Expr) ASSERT_IMPL(#Expr, Expr)

///
#define ASSERT_FALSE(Expr) ASSERT_IMPL(UTEST_STRINGIFY(!(Expr)), !(Expr))

///
#define ASSERT_EQ(A, B) ASSERT_IMPL(UTEST_STRINGIFY(A == B), (A == B))

///
#define ASSERT_NE(A, B) ASSERT_IMPL(UTEST_STRINGIFY(A != B), (A != B))

///
#define ASSERT_LT(A, B) ASSERT_IMPL(UTEST_STRINGIFY(A < B), (A < B))

///
#define ASSERT_LE(A, B) ASSERT_IMPL(UTEST_STRINGIFY(A <= B), (A <= B))

///
#define ASSERT_GT(A, B) ASSERT_IMPL(UTEST_STRINGIFY(A > B), (A > B))

///
#define ASSERT_GE(A, B) ASSERT_IMPL(UTEST_STRINGIFY(A >= B), (A >= B))

///
#define ASSERT_NOT_NULL(A) ASSERT_IMPL(UTEST_STRINGIFY(A != nullptr), (A != nullptr))

///
#define ASSERT_NULL(A) ASSERT_IMPL(UTEST_STRINGIFY(A == nullptr), (A == nullptr))

///
#define ASSERT_FLOAT_EQ(A, B) ASSERT_IMPL(UTEST_STRINGIFY(A == B), utest::is_approximately_equal(A, B))

///
#define ASSERT_FLOAT_NE(A, B) ASSERT_IMPL(UTEST_STRINGIFY(A != B), (!utest::is_approximately_equal(A, B)))

/// Assert floating point compare with tolerance.
#define ASSERT_FLOAT_EQ_T(A, B, T) ASSERT_IMPL(UTEST_STRINGIFY(A == B), utest::is_approximately_equal(A, B, T))

///
#define ASSERT_FLOAT_NE_T(A, B, T) ASSERT_IMPL(UTEST_STRINGIFY(A != B), (!utest::is_approximately_equal(A, B, T)))

///
#define ASSERT_STR_EQ(A, B) ASSERT_IMPL(UTEST_STRINGIFY(A == B), (std::string(A) == std::string(B)))

///
#define ASSERT_STR_NE(A, B) ASSERT_IMPL(UTEST_STRINGIFY(A != B), (std::string(A) != std::string(B)))

///
#define ASSERT_EXCEPTION(Expr, exception_type) ASSERT_EXCEPTION_IMPL(Expr, exception_type)

// MARK: - Macro implementations -

#ifdef _MSC_VER
  #define UTEST_MSVC_PUSH_WARNING(x) __pragma(warning(push)) __pragma(warning(disable : x))
  #define UTEST_MSVC_POP_WARNING() __pragma(warning(pop))

#else
  #define UTEST_MSVC_PUSH_WARNING(x)
  #define UTEST_MSVC_POP_WARNING()
#endif

// C4514: unreferenced inline function has been removed.
// C5045: mitigation.
UTEST_MSVC_PUSH_WARNING(4514 5045)

#if __cplusplus >= 201703L
  #define UTEST_INLINE_CONSTEXPR inline constexpr
  #define UTEST_NOEXCEPT noexcept
  #define UTEST_NORETURN [[noreturn]]
  #define UTEST_CONSTEXPR constexpr
  #define UTEST_INLINE_VARIABLE inline

#elif __cplusplus >= 201402L
  #define UTEST_INLINE_CONSTEXPR static constexpr
  #define UTEST_NOEXCEPT noexcept
  #define UTEST_NORETURN [[noreturn]]
  #define UTEST_CONSTEXPR constexpr
  #define UTEST_INLINE_VARIABLE static

#elif __cplusplus >= 201103L
  #define UTEST_INLINE_CONSTEXPR static constexpr
  #define UTEST_NOEXCEPT noexcept
  #define UTEST_NORETURN [[noreturn]]
  #define UTEST_CONSTEXPR constexpr
  #define UTEST_INLINE_VARIABLE static

#elif __cplusplus >= 199711L
  #define UTEST_INLINE_CONSTEXPR static
  #define UTEST_NOEXCEPT throw()

  #ifdef _MSC_VER
    #define UTEST_NORETURN __declspec(noreturn)
  #else
    #define UTEST_NORETURN __attribute__((noreturn))
  #endif // _MSC_VER

  #define UTEST_CONSTEXPR
  #define UTEST_INLINE_VARIABLE static

#else
  #error Unsupported cpp version
#endif

#define UTEST_STRINGIFY(X) UTEST_STR(X)
#define UTEST_STR(X) #X

#define EXPECT_IMPL(S, Expr)                                                                                           \
  UTEST_MSVC_PUSH_WARNING(4127)                                                                                        \
  try {                                                                                                                \
    utest::manager::state().check_count++;                                                                             \
    if (!(Expr)) {                                                                                                     \
      utest::manager::state().current_test_failed = true;                                                              \
      utest::manager::state().failed_check_count++;                                                                    \
      utest::manager::state().add_check(false, S, __FILE__, __LINE__);                                                 \
      std::cout << "    > Check failed\n      expected : " << S << "\n      source   : " << __FILE__                   \
                << "\n      line     : " << __LINE__ << "\n";                                                          \
    }                                                                                                                  \
    else {                                                                                                             \
      utest::manager::state().add_check(true, S, __FILE__, __LINE__);                                                  \
    }                                                                                                                  \
  } catch (const std::exception& e) {                                                                                  \
    throw e;                                                                                                           \
  }                                                                                                                    \
  UTEST_MSVC_POP_WARNING()

#define EXPECT_EXCEPTION_IMPL(Expr, exception_type)                                                                    \
  do {                                                                                                                 \
    int exception_caught = 0;                                                                                          \
    try {                                                                                                              \
      utest::manager::state().check_count++;                                                                           \
      (Expr);                                                                                                          \
    } catch (const exception_type&) {                                                                                  \
      exception_caught = 1;                                                                                            \
    } catch (...) {                                                                                                    \
      exception_caught = 2;                                                                                            \
    }                                                                                                                  \
                                                                                                                       \
    if (exception_caught != 1) {                                                                                       \
      utest::manager::state().current_test_failed = true;                                                              \
      utest::manager::state().failed_check_count++;                                                                    \
      std::cout << "    > Check exception failed\n      expected : " << UTEST_STRINGIFY(exception_type)                \
                << "\n      got      : " << (exception_caught == 2 ? "unexpected exception" : "no exception")          \
                << "\n      source   : " << __FILE__ << "\n      line     : " << __LINE__ << "\n";                     \
    }                                                                                                                  \
  } while (0)

#define ASSERT_IMPL(S, Expr)                                                                                           \
  utest::manager::state().check_count++;                                                                               \
  utest::custom_assert(S, Expr, __FILE__, __LINE__)

#define ASSERT_EXCEPTION_IMPL(Expr, exception_type)                                                                    \
  do {                                                                                                                 \
    int exception_caught = 0;                                                                                          \
    try {                                                                                                              \
      utest::manager::state().check_count++;                                                                           \
      (Expr);                                                                                                          \
    } catch (const exception_type&) {                                                                                  \
      exception_caught = 1;                                                                                            \
    } catch (...) {                                                                                                    \
      exception_caught = 2;                                                                                            \
    }                                                                                                                  \
    if (exception_caught != 1) {                                                                                       \
      utest::manager::state().current_test_failed = true;                                                              \
      utest::manager::state().failed_check_count++;                                                                    \
      utest::custom_exception(UTEST_STRINGIFY(exception_type), exception_caught == 2, __FILE__, __LINE__);             \
    }                                                                                                                  \
  } while (0)

#ifdef _MSC_VER
  #define UTEST_CASE_IMPL(group, name, desc)                                                                           \
    void name();                                                                                                       \
    namespace __unit_tests {                                                                                           \
      namespace {                                                                                                      \
        struct name##__TestRegistration {                                                                              \
          inline name##__TestRegistration() { utest::manager::add_test(group, #name, desc, &name); }                   \
        };                                                                                                             \
        static name##__TestRegistration name##__testRegistration = name##__TestRegistration{};                         \
      } /* namespace */                                                                                                \
    } /* namespace __unit_tests */                                                                                     \
    void name()

#else
  #define UTEST_CASE_IMPL(group, name, desc)                                                                           \
    void name();                                                                                                       \
    namespace __unit_tests {                                                                                           \
      namespace {                                                                                                      \
        __attribute__((constructor)) static void name##__TestRegistration() {                                          \
          utest::manager::add_test(group, #name, desc, &name);                                                         \
        }                                                                                                              \
      } /* namespace */                                                                                                \
    } /* namespace __unit_tests */                                                                                     \
    void name()
#endif

namespace utest {

// MARK: - Asserts and Exceptions -

template <class = void>
class test_exception : public std::exception {
public:
  virtual ~test_exception() UTEST_NOEXCEPT override = default;
};

template <class = void>
class failed_expect_exception : public test_exception<> {
public:
  inline failed_expect_exception(const char* expr_str, const char* file, int line)
      : m_error_str(create_message(expr_str, file, line)) {}

  virtual ~failed_expect_exception() UTEST_NOEXCEPT override = default;

  virtual const char* what() const UTEST_NOEXCEPT override { return m_error_str.c_str(); }

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

  virtual ~failed_exception() UTEST_NOEXCEPT override = default;

  inline virtual const char* what() const UTEST_NOEXCEPT override { return m_error_str.c_str(); }

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
  throw utest::failed_expect_exception<>(expr_str, file, line);
}

UTEST_NORETURN inline void custom_exception(const char* expr_str, bool is_caught, const char* file, int line) {
  throw utest::failed_exception<>(is_caught ? "unexpected exception" : "no exception", expr_str, file, line);
}

namespace detail {
  template <typename... T>
  using float_common_return_t =
      typename std::conditional<std::is_integral<typename std::common_type<T...>::type>::value, float,
          typename std::common_type<T...>::type>::type;

  template <class StartT>
  inline UTEST_CONSTEXPR std::chrono::microseconds::rep get_us_count(const StartT& start) {
    return std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - start)
        .count();
  }

  UTEST_INLINE_CONSTEXPR const char* kOk = "[       OK ]";
  UTEST_INLINE_CONSTEXPR const char* kFailed = "[  FAILED  ]";

  UTEST_INLINE_CONSTEXPR const char* kTest = "test";
  UTEST_INLINE_CONSTEXPR const char* kTests = "tests";
} // namespace detail

// MARK: - Test data -

typedef void (*test_function)();

struct test_item {
  std::string name;
  std::string desc;
  test_function fct;
};

// MARK: - Test results -

struct check_result {
  check_result() = default;
  inline check_result(const char* g, const test_item* item, const char* expr, const char* f, std::size_t l,
      std::size_t end_time, bool s)
      : group(g)
      , item(item)
      , expr(expr)
      , file(f)
      , line(l)
      , end_time(end_time)
      , success(s)
      , reserved{} {}

  const char* group;
  const test_item* item;
  const char* expr;

  const char* file;
  std::size_t line;
  std::size_t end_time;
  bool success;
  char reserved[7];
};

// MARK: - Tests manager -

class manager {
public:
  using test_vector = std::vector<test_item>;
  using test_map = std::map<std::string, test_vector>;

  struct state {
    using clock = std::chrono::high_resolution_clock;

    const test_item* current_item = nullptr;
    std::size_t passed_count = 0;
    std::size_t failed_count = 0;
    std::size_t total_tests = 0;
    std::size_t check_count = 0;
    std::size_t failed_check_count = 0;

    clock::time_point launch_start_time;
    clock::time_point group_start_time;
    clock::time_point test_start_time;

    const char* current_group;
    const char* current_test;

    std::vector<check_result> results;

    bool current_test_failed = false;
    char reserved[7];

    inline void add_check(bool success, const char* expr, const char* file, std::size_t line) {
      results.push_back(check_result(current_group, current_item, expr, file, line,
          static_cast<std::size_t>(detail::get_us_count(test_start_time)), success));
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

      std::cout << "[ RUN      ] > test case " << t.name << std::endl;

      try {
        t.fct();
      } catch (const utest::test_exception<>& e) {
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
    }

    inline void report(bool passed) {
      if (passed) {
        std::cout << detail::kOk << " < test case " << current_test << " (" << check_count << " checks) (" << test_us()
                  << " us)" << std::endl;
      }
      else {
        std::cout << detail::kFailed << " < test case " << current_test << " (" << (check_count - failed_check_count)
                  << '/' << check_count << " checks) (" << test_us() << " us)" << std::endl;
      }
    }

    inline std::chrono::microseconds::rep test_us() const { return detail::get_us_count(test_start_time); }

    inline std::chrono::microseconds::rep group_us() const { return detail::get_us_count(group_start_time); }

    inline std::chrono::microseconds::rep launch_us() const { return detail::get_us_count(launch_start_time); }

    inline static UTEST_CONSTEXPR const char* test(std::size_t count) {
      return count <= 1 ? detail::kTest : detail::kTests;
    }
  };

  static inline manager& get_instance() {
    static manager tm;
    return tm;
  }

  static inline state& state() { return get_instance().m_state; }

  static inline void add_test(const char* group, const char* name, const char* desc, test_function fct) {
    test_vector& vec = get_instance().m_tests[group];
    test_item item{ name, desc, fct };
    vec.insert(std::upper_bound(vec.begin(), vec.end(), item, item_comparator()), std::move(item));
  }

  inline static int run(int argc, const char* argv[]);

private:
  manager() = default;
  test_map m_tests;
  struct state m_state;

  inline int run_impl(int argc, const char* argv[]);

  struct item_comparator {
    inline bool operator()(const test_item& a, const test_item& b) const { return a.name < b.name; }
  };
};

// MARK: - Inline implementations -

template <typename T1, typename T2>
inline bool is_approximately_equal(T1 a, T2 b,
    detail::float_common_return_t<T1, T2> tolerance
    = std::numeric_limits<detail::float_common_return_t<T1, T2> /**/>::epsilon()) {
  using ftype = detail::float_common_return_t<T1, T2>;

  const ftype fa = static_cast<ftype>(a);
  const ftype fb = static_cast<ftype>(b);
  return (std::abs(fa - fb) <= tolerance) || (std::abs(fa - fb) < (std::max(std::abs(fa), std::abs(fb)) * tolerance));
}

int manager::run(int argc, const char* argv[]) { return get_instance().run_impl(argc, argv); }

int manager::run_impl(int, const char*[]) {

  m_state.passed_count = 0;
  m_state.failed_count = 0;
  m_state.total_tests = 0;

  for (const auto& g : m_tests) {
    m_state.total_tests += g.second.size();
  }

  std::cout << "[==========] Running " << m_state.total_tests << " " << state::test(m_state.total_tests) << " from "
            << m_tests.size() << " test groups.\n\n";

  m_state.launch_start_time = state::clock::now();
  for (const auto& g : m_tests) {
    m_state.start_group(g);

    for (const auto& t : g.second) {
      m_state.run_test(t);
    }

    m_state.end_group(g);
  }

  std::cout << "[==========] " << m_state.total_tests << " " << state::test(m_state.total_tests) << " from "
            << m_tests.size() << " test groups (" << m_state.launch_us() << " us)." << std::endl;

  std::cout << "[  PASSED  ] " << m_state.passed_count << " " << state::test(m_state.passed_count) << std::endl;

  if (m_state.failed_count) {
    std::cout << "[  FAILED  ] " << m_state.failed_count << " " << state::test(m_state.failed_count) << std::endl;
  }

  return static_cast<int>(m_state.failed_count);
}

inline int run(int argc, const char* argv[]) { return manager::run(argc, argv); }
} // namespace utest.

UTEST_MSVC_POP_WARNING()
