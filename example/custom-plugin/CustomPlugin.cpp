#include "CustomPlugin.hpp"
#include "dlplugincreator.h"

#include <stdio.h>
#include <memory>

CustomPlugin::~CustomPlugin()
{
    printf("Destroyed.");
}

int CustomPlugin::plugin(const std::string &pluginWorkingPath)
{
    printf("Custom Plugin Plugged! \n");

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

// Plugin  Factory

extern "C" std::shared_ptr<IPlugin> create() {
    return std::make_shared<CustomPlugin>();
}
