#include <string>

#include "gtest/gtest.h"

#include "PluginManagerTest.hpp"
// #include "PluginArchive.hpp"

// TEST(PluginArchiveTest, export)
// {

// }

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    int ret = RUN_ALL_TESTS();
    return ret;
}

