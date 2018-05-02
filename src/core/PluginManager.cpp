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
    if (_factory->plugins().empty())
    {
        return;
    }

    for (std::shared_ptr<IPlugin> plugin : _factory->plugins())
    {
        std::cout << "Checking plugin proxy: " << plugin->pluginName() << std::endl;
        std::cout << "\tProxy: " << plugin->proxyId() << std::endl;
        if (_proxyList.count(plugin->proxyId()) > 0)
        {
            if (_proxyList[plugin->proxyId()]->addPlugin(plugin))
            {
                _hasLoadedPlugins = true;
            }
        }
        else
        {
            std::cout << "Proxy \"" << plugin->proxyId() << "\" not found." << std::endl;
        }
        std::cout << std::endl;
    }
}

PluginManager::PluginManager() :
_initialized(false),
_factory(nullptr),
_hasLoadedPlugins(false)
{
}

bool PluginManager::init(const ILibFinder &libFinder)
{
    bool rc = false;
    std::vector<std::string> libsPath = libFinder.libsPath();

    if (_factory != nullptr && _factory->createPlugins(libsPath) >= 0)
    {
        _addPluginsToProxies();
        _initializeProxies();

        rc = _initialized = true;
    }

    return rc;
}

bool PluginManager::initialized() const
{
    return _initialized;
}

bool PluginManager::hasLoadedPlugins() const
{
    return _hasLoadedPlugins;
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

bool PluginManager::registerFactory(std::shared_ptr<PluginFactory> factory)
{
    if (factory != nullptr)
    {
        _factory = factory;
        return true;
    }

    return false;
}
