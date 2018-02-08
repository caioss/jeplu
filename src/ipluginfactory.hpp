#ifndef IPLUGINFACTORY_H
#define IPLUGINFACTORY_H

#include <memory>
#include <string>
#include <vector>

#include "iplugin.hpp"
#include "ipluginloader.hpp"

class IPluginFactory
{
public:
    virtual int createPlugins(const std::vector<std::string> &pluginsPaths) = 0;

    virtual std::vector<std::shared_ptr<IPlugin>> getPlugins() const = 0;

    virtual bool registerLoader(std::shared_ptr<IPluginLoader> loader) = 0;
};

#endif
