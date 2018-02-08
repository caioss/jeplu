#ifndef PLUGINFACTORY_H
#define PLUGINFACTORY_H

#include <memory>

#include "ipluginfactory.hpp"
#include "ipluginloader.hpp"

class PluginFactory : public IPluginFactory
{
private:
    std::vector<std::shared_ptr<IPlugin>> _plugins;

    std::vector<std::shared_ptr<IPluginLoader>> _loaders;

public:
    PluginFactory();

    int createPlugins(const std::vector<std::string> &pluginsPaths) override;

    std::vector<std::shared_ptr<IPlugin>> getPlugins() const override;

    bool registerLoader(std::shared_ptr<IPluginLoader> loader) override;
};

#endif
