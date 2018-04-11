#include "Jeplu.hpp"

#include "gtest/gtest.h"

// Test function
bool testTrue(bool value)
{
    Jeplu j;
    j.init("./");

    return value;
}

// Test assignment
TEST(testTrue, TestTrue) {
    EXPECT_EQ(true, testTrue(false));
}

