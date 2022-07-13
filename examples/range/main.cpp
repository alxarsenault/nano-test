#include "nano/test.h"

namespace {
TEST_CASE("Example", Range) {
  int a[] = { 1, 2, 3 };
  long b[] = { 1, 2, 4 };

  EXPECT_RANGE_EQ(&a[0], &b[0], 2);
  EXPECT_RANGE_GE(&a[0], &b[0], 2);
  //   ASSERT_RANGE_EQ(&a[0], &b[0], 3);
}
} // namespace.

NANO_TEST_MAIN()
