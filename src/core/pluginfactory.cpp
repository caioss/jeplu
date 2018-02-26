#include "pluginfactory.hpp"

#include <vector>
#include <iostream>

PluginFactory::PluginFactory()
{
}

int PluginFactory::createPlugins(const std::vector<std::string> &pluginsPaths)
{
    std::vector<std::shared_ptr<IPlugin>> loadedPlugins;

    for(const std::string &libPath : pluginsPaths)
    {
        std::cout << "Loading lib: " << libPath << std::endl;
        for(std::shared_ptr<IPluginLoader> loader : _loaders)
        {
            std::shared_ptr<IPlugin> plugin = nullptr;
            int rc = loader->loadPlugin(libPath, plugin);
            if (rc == 0)
            {
                loadedPlugins.push_back(plugin);
                std::cout << "Plugin " << plugin->pluginName().c_str() << " loaded!" << std::endl;
                break;
            } else {
                std::cout << "Unable to load plugin with " << loader->name() << " loader..." << std::endl;
            }
        }
    }

    if (!loadedPlugins.empty())
    {
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
    if (loader == nullptr)
    {
        return false;
    }
    _loaders.push_back(loader);
    return true;
}
