#ifndef JEPLUTEST_HPP
#define JEPLUTEST_HPP

#include <stdio.h>

#include "gtest/gtest.h"

#include "QCustomAdapter.hpp"
#include "Jeplu.hpp"

/**
 *  \brief This class tests the \c Jeplu framework.
 */
class JepluTest : public ::testing::Test
{
protected:
    JepluTest() : _pluginsPath("plugins/")
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

    /**
     *  \brief The jeplu object.
     */
    Jeplu _jeplu;

    /**
     *  \brief Holds the path that contains the plugins.
     */
    std::string _pluginsPath;
};

TEST_F(JepluTest, initJeplu)
{
    ASSERT_EQ(JepluErrs::OK, _jeplu.init(_pluginsPath));
}

TEST_F(JepluTest, checkPluginIsEmpty)
{
    _jeplu.init(_pluginsPath);

    ASSERT_EQ(false, _jeplu.hasLoadedPlugins());
}

TEST_F(JepluTest, testAdapter)
{
    std::shared_ptr<QCustomAdapter> adapter = std::make_shared<QCustomAdapter>();

    _jeplu.registerAdapter(adapter);
    _jeplu.init(_pluginsPath);

    ASSERT_EQ(true ,adapter->hasPluginsLoaded());
}

#endif //JEPLUTEST_HPP
