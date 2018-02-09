#include "customplugin.hpp"
#include "dlplugincreator.hpp"

#include <stdio.h>
#include <memory>

CustomPlugin::~CustomPlugin()
{
    printf("Destroyed.");
}

void CustomPlugin::plugin()
{
    printf("Custom Plugin Plugged! \n");
}

std::string CustomPlugin::pluginName()
{
    return "CustomPlugin";
}

// Plugin  Factory

extern "C" std::shared_ptr<IPlugin> create() {
    return std::make_shared<CustomPlugin>();
}
