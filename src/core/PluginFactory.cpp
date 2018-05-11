#include "PluginFactory.hpp"

#include <vector>
#include <iostream>

PluginFactory::PluginFactory()
{
}

int PluginFactory::createPlugins(const std::vector<std::string> &pluginsPath)
{
    std::vector<std::shared_ptr<IPlugin>> pluginsCreated;
    // If there are no loader available, we can't create plugins
    if (_loaders.empty())
    {
        return -1;
    }
    int rerr = 0;

    for(const std::string &libPath : pluginsPath)
    {
        std::cout << "Loading lib: " << libPath << std::endl;
        for(std::shared_ptr<IPluginLoader> loader : _loaders)
        {
            std::cout << "Trying loader: " << loader->name() << std::endl;
            std::shared_ptr<IPlugin> plugin = nullptr;
            if (loader->loadPlugin(libPath, plugin) == LoadingErrs::OK)
            {
                pluginsCreated.push_back(plugin);
                std::cout << "Plugin " << plugin->pluginName().c_str() << " loaded!" << std::endl;
                break;
            }
            else
            {
                std::cout << "Unable to load plugin. Err: " << loader->errString() << std::endl;
            }
        }
    }

    if (pluginsCreated.empty())
    {
        std::cout << "No plugins loaded." << std::endl;
        rerr = 1;
    }
    else
    {
        _plugins.insert(_plugins.end(), pluginsCreated.begin(), pluginsCreated.end());
    }
    return rerr;
}

bool PluginFactory::hasPlugins() const
{
    return !_plugins.empty();
}

std::vector<std::shared_ptr<IPlugin>> PluginFactory::plugins() const
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
