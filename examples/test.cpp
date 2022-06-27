#include "utest.h"
#include <stdexcept>

namespace {

TEST_CASE("Utils", Minimum, "") {
  int a = 0;
  EXPECT_NOT_NULL(&a);
  EXPECT_NULL(nullptr);

  EXPECT_EQ(1, 1);
  EXPECT_NE(0, 1);

  EXPECT_LT(5, 6);
  EXPECT_LE(5, 6);
  EXPECT_LE(5, 5);

  EXPECT_GT(7, 6);
  EXPECT_GE(7, 6);
  EXPECT_GE(5, 5);

  EXPECT_STR_EQ("A", "A");
  EXPECT_STR_NE("A", "B");

  EXPECT_FLOAT_EQ(2.2f, 2.2f);
  EXPECT_FLOAT_EQ(2.2000001f, 2.2f);

  EXPECT_FLOAT_NE(2.2f, 2.3f);

  EXPECT_FLOAT_EQ_T(4.5f, 4.5f, 0.1f);
  EXPECT_FLOAT_EQ_T(4.5f, 4.6f, 0.1f);

  EXPECT_FLOAT_NE_T(4.5f, 4.7f, 0.01f);
}

TEST_CASE("Utils", Minimum2, "Check \"expression") {
  int a = 0;
  EXPECT_NOT_NULL(&a);
  EXPECT_NULL(nullptr);

  EXPECT_EQ(3, 3);
  EXPECT_NE(0, 1);

  EXPECT_LT(5, 6);
  EXPECT_LE(5, 6);
  EXPECT_LE(5, 5);

  EXPECT_STR_EQ("A", "A");
  EXPECT_STR_NE("A", "B");

  EXPECT_FLOAT_EQ(2.2f, 2.2f);
  EXPECT_FLOAT_EQ(2.2000001f, 2.2f);

  EXPECT_FLOAT_NE(2.2f, 2.3f);

  EXPECT_FLOAT_EQ_T(4.5f, 4.5f, 0.1f);
  EXPECT_FLOAT_EQ_T(4.5f, 4.6f, 0.1f);

  EXPECT_FLOAT_NE_T(4.5f, 4.7f, 0.01f);

  ASSERT_EXCEPTION([]() { throw std::range_error("bad range"); }(), std::range_error);
  EXPECT_EXCEPTION([]() { throw std::range_error("bad range"); }(), std::exception);
  // ASSERT_EXCEPTION([]() { throw std::range_error("bad range"); }(), std::bad_cast);

  ASSERT_EQ(5, 6);
}
} // namespace.
