#include "QCustomProxy.hpp"

#include "ICustomInterface.hpp"

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

std::string QCustomProxy::proxyId() const
{
    return "qcustomproxy.proxy.jeplu";
}

bool QCustomProxy::initialized() const
{
    return _initialized;
}

std::vector<std::weak_ptr<IPlugin>> QCustomProxy::getPlugins() const
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
