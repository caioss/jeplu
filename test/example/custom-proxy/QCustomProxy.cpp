#include "QCustomProxy.hpp"

#include <iostream>

QCustomProxy::QCustomProxy()
: _initialized(false)
{
}

QCustomProxy::~QCustomProxy()
{
}

bool QCustomProxy::init(std::vector<std::weak_ptr<IPlugin>> plugins)
{
    _initialized = true;

    return _initialized;
}

bool QCustomProxy::hasPluginsLoaded() const
{
    return !_plugins.empty();
}

std::string QCustomProxy::proxyId() const
{
    return "qcustomproxy.proxy.jeplu";
}

bool QCustomProxy::initialized() const
{
    return _initialized;
}

std::vector<std::weak_ptr<IPlugin>> QCustomProxy::plugins() const
{
    return _plugins;
}

bool QCustomProxy::addPlugin(std::weak_ptr<IPlugin> plugin)
{
    std::shared_ptr<IPlugin> sharedPlugin = plugin.lock();
    std::shared_ptr<ICustomInterface> customPlugin = std::dynamic_pointer_cast<ICustomInterface>(sharedPlugin);
    if (customPlugin != nullptr && customPlugin->customFunction())
    {
        std::cout << "Plugin " << customPlugin->pluginName() << " compatible with proxy." << std::endl;
        _plugins.push_back(plugin);

        return true;
    }
    return false;
}

std::vector<std::weak_ptr<ICustomInterface>> QCustomProxy::interfaces() const
{
    std::vector<std::weak_ptr<ICustomInterface>> interfaces;
    for (std::weak_ptr<IPlugin> plugin : _plugins)
    {
        std::shared_ptr<IPlugin> pluginLocked = plugin.lock();
        if (pluginLocked)
        {
            interfaces.push_back(std::dynamic_pointer_cast<ICustomInterface>(pluginLocked));
        }
    }
    return interfaces;
}
