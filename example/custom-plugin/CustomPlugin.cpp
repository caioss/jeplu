#include "CustomPlugin.hpp"
#include "dlplugincreator.h"

#include <iostream>
#include <memory>

CustomPlugin::~CustomPlugin()
{
    std::cout << "Destroyed." << std::endl;
}

int CustomPlugin::plugin(const std::string &pluginWorkingPath)
{
    std::cout << "Custom Plugin Plugged!" << std::endl;

    return 0;
}

std::string CustomPlugin::pluginName() const
{
    return "CustomPlugin";
}

std::string CustomPlugin::pluginId() const
{
    return "CustomPlugin.example.jeplu";
}

int CustomPlugin::pluginVersion() const
{
    return 1;
}

std::string CustomPlugin::proxyId() const
{
    return "";
}

// Plugin Creator

extern "C" std::shared_ptr<IPlugin> create() {
    return std::make_shared<CustomPlugin>();
}
