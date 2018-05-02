#ifndef PLUGINMANAGERTEST_HPP
#define PLUGINMANAGERTEST_HPP
#include <stdio.h>

#include "gtest/gtest.h"

#include "core/PluginManager.hpp"
#include "FakeLibFinder.hpp"

/**
 *  \brief This class tests the \c PluginManager class.
 */
class PluginManagerTest : public ::testing::Test
{
protected:
    // You can remove any or all of the following functions if its body
    // is empty.

    PluginManagerTest()
    {
        // You can do set-up work for each test here.
    }

    virtual ~PluginManagerTest()
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
    PluginManager _manager;
};

TEST_F(PluginManagerTest, initWithoutFactory)
{
    FakeLibFinder finder(".");
    _manager.init(finder);
    ASSERT_EQ(false, _manager.initialized());
}

#endif //PLUGINMANAGERTEST_HPP
