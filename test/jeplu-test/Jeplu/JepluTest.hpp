#ifndef JEPLUTEST_HPP
#define JEPLUTEST_HPP

#include <stdio.h>

#include "gtest/gtest.h"

#include "Jeplu.hpp"

/**
 *  \brief This class tests the \c Jeplu framework.
 */
class JepluTest : public ::testing::Test
{
protected:
    // You can remove any or all of the following functions if its body
    // is empty.

    JepluTest()
    {
        // You can do set-up work for each test here.
    }

    virtual ~JepluTest()
    {
        // You can do clean-up work that doesn't throw exceptions here.
    }

    // If the constructor and destructor are not enough for setting up
    // and cleaning up each test, you can define the following methods:
    virtual void SetUp()
    {
        // Code here will be called immediately after the constructor (right
        // before each test).
    }

    virtual void TearDown()
    {
        // Code here will be called immediately after each test (right
        // before the destructor).
    }

    // Objects declared here can be used by all tests in the test case for Foo.
    Jeplu _jeplu;
};

TEST_F(JepluTest, initJeplu)
{
    ASSERT_EQ(0, _jeplu.init("plugins/"));
}

TEST_F(JepluTest, checkPluginIsEmpty)
{
    _jeplu.init("plugins/");

    ASSERT_EQ(false, _jeplu.hasLoadedPlugins());
}

#endif //JEPLUTEST_HPP
