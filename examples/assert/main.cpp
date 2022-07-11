#include "nano/utest.h"

namespace {
inline void foo_throw(bool err) {
  if (err) {
    throw std::range_error("bad range");
  }
}

TEST_CASE("Example", Exception, "Check exceptions", NANO_TEST_ABORT_ON_ERROR) {
  ASSERT_EXCEPTION(foo_throw(true), std::range_error);
  EXPECT_EXCEPTION(foo_throw(true), std::exception);
  ASSERT_EXCEPTION(foo_throw(true), std::bad_cast);
}
} // namespace.

NANO_TEST_MAIN()
