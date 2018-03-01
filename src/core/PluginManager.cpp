#include "PluginManager.hpp"
#include "PluginFactory.hpp"

#include <iostream>

void PluginManager::_initializeProxies()
{
    for (auto it = _proxyList.begin();
         it != _proxyList.end(); ++it)
    {
        it->second->init();
    }
}

void PluginManager::_addPluginsToProxies()
{
    for (std::shared_ptr<IPlugin> plugin : _factory->getPlugins())
    {
        std::cout << "Checking plugin proxy: " << plugin->pluginName() << std::endl;
        std::cout << "\tProxy: " << plugin->proxyId() << std::endl;
        if (_proxyList.count(plugin->proxyId()) > 0)
        {
            _proxyList[plugin->proxyId()]->addPlugin(plugin);
        }
        else
        {
            std::cout << "Proxy \"" << plugin->proxyId() << "\" not found." << std::endl;
        }
        std::cout << std::endl;
    }
}

PluginManager::PluginManager()
: _factory(nullptr)
{
}

bool PluginManager::init(const std::string &path)
{
    // todo: find plugins .lib files
    std::vector<std::string> libsPath;
    libsPath.push_back("plugins/libqcustom_plugin.so");
    libsPath.push_back("plugins/libcustom_plugin.so");
    if (_factory == nullptr)
    {
        return false;
    }

    if (_factory->createPlugins(libsPath) == 0)
    {
        _addPluginsToProxies();
        _initializeProxies();

        return true;
    }

    return false;
}

bool PluginManager::registerProxy(std::shared_ptr<IPluginProxy> proxy)
{
    if (proxy != nullptr)
    {
        _proxyList.emplace(proxy->proxyId(), proxy);
        return true;
    }

    return false;
}

bool PluginManager::registerFactory(std::shared_ptr<IPluginFactory> factory)
{
    if (factory != nullptr)
    {
        _factory = factory;
        return true;
    }

    return false;
}
