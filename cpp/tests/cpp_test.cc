#include "../src/cpp.hh"
#include <gtest/gtest.h>

TEST(AddTest, SimpleAssertions) {
   EXPECT_EQ(add(1, 1), 2);
}