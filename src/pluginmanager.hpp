#ifndef PLUGINMANAGER_H
#define PLUGINMANAGER_H

#include "ipluginmanager.hpp"
#include "pluginfactory.hpp"

class PluginManager : public IPluginManager
{
private:
    std::shared_ptr<IPluginFactory> _factory;

    std::vector<std::shared_ptr<IPluginProxy>> _proxyList;
public:
    PluginManager();

    bool init(const std::string &path);

    bool registerFactory(std::shared_ptr<IPluginFactory> factory);

    bool registerProxy(std::shared_ptr<IPluginProxy> proxy) override;
};

#endif
