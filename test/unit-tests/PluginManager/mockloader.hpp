#ifndef MOCKLOADER_HPP
#define MOCKLOADER_HPP

#include "IPluginLoader.hpp"

#include "gmock/gmock.h"  // Brings in Google Mock.

class MockLoader : public IPluginLoader
{
public:
        MOCK_METHOD2(loadPlugin, int(const std::string &pluginPath, std::shared_ptr<IPlugin> &plugin));
        MOCK_CONST_METHOD0(name, std::string());
        MOCK_CONST_METHOD0(errString, std::string());
};

#endif
