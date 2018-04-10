#include "gtest/gtest.h"

// Test function
bool testTrue(bool value)
{
    return value;
}

// Test assignment
TEST(testTrue, TestTrue) {
    EXPECT_EQ(true, testTrue(false));
}
