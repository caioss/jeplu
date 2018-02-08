#ifndef IPLUGINMANAGER_H
#define IPLUGINMANAGER_H

#include "ipluginproxy.hpp"

class IPluginManager
{
public:
    virtual bool registerProxy(std::shared_ptr<IPluginProxy> proxy) = 0;
};

#endif
