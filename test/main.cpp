#include "gtest/gtest.h"

#include "PluginManagerTest.hpp"
#include "JepluTest.hpp"

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    int ret = RUN_ALL_TESTS();
    return ret;
}
