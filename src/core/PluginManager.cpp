#include "PluginManager.hpp"
#include "ILibFinder.hpp"
#include "IPluginAdapter.hpp"
#include "PluginFactory.hpp"

#include <iostream>

void PluginManager::_initializeAdapters()
{
    for (auto it = _adapterList.begin();
         it != _adapterList.end(); ++it)
    {
        it->second->init();
    }
}

void PluginManager::_addPluginsToAdapters()
{
    if (_factory->plugins().empty())
    {
        return;
    }

    for (std::shared_ptr<IPlugin> plugin : _factory->plugins())
    {
        std::cout << "Checking plugin adapter: " << plugin->pluginName() << std::endl;
        std::cout << "\tAdapter: " << plugin->adapterId() << std::endl;
        if (_adapterList.count(plugin->adapterId()) > 0)
        {
            if (_adapterList[plugin->adapterId()]->addPlugin(plugin))
            {
                _hasLoadedPlugins = true;
            }
        }
        else
        {
            std::cout << "Adapter \"" << plugin->adapterId() << "\" not found." << std::endl;
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

bool PluginManager::init(std::unique_ptr<ILibFinder> libFinder)
{
    if (!libFinder)
    {
        return false;
    }

    bool rc = false;
    std::vector<std::string> libsPath = libFinder->libsPath();

    if (_factory != nullptr && _factory->createPlugins(libsPath) >= 0)
    {
        _addPluginsToAdapters();
        _initializeAdapters();

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

bool PluginManager::registerAdapter(std::shared_ptr<IPluginAdapter> adapter)
{
    if (adapter != nullptr)
    {
        _adapterList.emplace(adapter->adapterId(), adapter);
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
