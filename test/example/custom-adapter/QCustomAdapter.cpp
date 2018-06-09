#include "QCustomAdapter.hpp"

#include "ICustomInterface.hpp"

#include <iostream>

QCustomAdapter::QCustomAdapter()
: _initialized(false)
{
}

QCustomAdapter::~QCustomAdapter()
{
}

bool QCustomAdapter::init(std::vector<std::weak_ptr<IPlugin>> plugins)
{
    _initialized = true;

    return _initialized;
}

bool QCustomAdapter::hasPluginsLoaded() const
{
    return !_plugins.empty();
}

std::string QCustomAdapter::adapterId() const
{
    return "qcustomadapter.adapter.jeplu";
}

bool QCustomAdapter::initialized() const
{
    return _initialized;
}

std::vector<std::weak_ptr<IPlugin>> QCustomAdapter::plugins() const
{
    return _plugins;
}

bool QCustomAdapter::addPlugin(std::weak_ptr<IPlugin> plugin)
{
    std::shared_ptr<IPlugin> sharedPlugin = plugin.lock();
    std::shared_ptr<ICustomInterface> customPlugin = std::dynamic_pointer_cast<ICustomInterface>(sharedPlugin);
    if (customPlugin != nullptr && customPlugin->customFunction())
    {
        std::cout << "Plugin " << customPlugin->pluginName() << " compatible with adapter." << std::endl;
        _plugins.push_back(plugin);

        return true;
    }
    return false;
}

std::vector<std::weak_ptr<ICustomInterface>> QCustomAdapter::interfaces() const
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
