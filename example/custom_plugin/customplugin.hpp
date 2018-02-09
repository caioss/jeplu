#ifndef CUSTOMPLUGIN_H
#define CUSTOMPLUGIN_H

#include <string.h>

#include "iplugin.hpp"

class CustomPlugin : public IPlugin
{
public:
    CustomPlugin() {}

    ~CustomPlugin();

    void plugin() override;

    std::string  pluginName() override;
};

#endif
