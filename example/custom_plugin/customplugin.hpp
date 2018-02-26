#ifndef CUSTOMPLUGIN_H
#define CUSTOMPLUGIN_H

#include <string.h>

#include "iplugin.hpp"

class CustomPlugin : public IPlugin
{
public:
    CustomPlugin() {}

    ~CustomPlugin();

    int plugin(const std::string &pluginWorkingPath) override;

    std::string pluginName() const override;

    std::string pluginId() const override;

    int pluginVersion() const override;

    std::string proxyId() const override;
};

#endif
