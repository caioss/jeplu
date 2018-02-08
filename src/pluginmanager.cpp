#include "pluginmanager.hpp"

#include "pluginfactory.hpp"

PluginManager::PluginManager() :
    _factory(nullptr)
{
}

bool PluginManager::init(const std::string &path)
{
    // todo: find plugins .lib files
    std::vector<std::string> libsPath;
    if (_factory != nullptr) {
        _factory->createPlugins(libsPath);

        return true;
    }

    return false;
}

bool PluginManager::registerProxy(std::shared_ptr<IPluginProxy> proxy)
{
    if (proxy != nullptr) {
        _proxyList.push_back(proxy);
        return true;
    }

    return false;
}

bool PluginManager::registerFactory(std::shared_ptr<IPluginFactory> factory)
{
    if (factory != nullptr) {
        _factory = factory;
        return true;
    }

    return false;
}
