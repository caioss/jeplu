#include "gtest/gtest.h"

#include "PluginManagerTest.hpp"
#include "PluginArchive.hpp"

bool testTrue(void)
{
    PluginArchive pluginArchive;

    return pluginArchive.exportPlugin("/tmp/test.zip",
                                      "/tmp/simulador");
}

TEST(testTrue, TestTrue)
{
    EXPECT_EQ(true, testTrue());
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    int ret = RUN_ALL_TESTS();
    return ret;
}

