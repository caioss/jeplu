#include "pluginfactory.hpp"

#include <iostream>

PluginFactory::PluginFactory()
{
}

int PluginFactory::createPlugins(const std::vector<std::string> &pluginsPaths)
{
    std::vector<std::shared_ptr<IPlugin>> loadedPlugins;
    std::vector<std::string> unloadedPaths = pluginsPaths;
    for(std::shared_ptr<IPluginLoader> loader : _loaders) {
        unloadedPaths = loader->loadPlugins(unloadedPaths, loadedPlugins);
    }

    if (!loadedPlugins.empty()) {
      _plugins = loadedPlugins;
    }
  
    return 0;
}

std::vector<std::shared_ptr<IPlugin>> PluginFactory::getPlugins() const
{
    return _plugins;
}

bool PluginFactory::registerLoader(std::shared_ptr<IPluginLoader> loader)
{
    if (loader == nullptr) {
        return false;
    }
    _loaders.push_back(loader);
    return true;
}
