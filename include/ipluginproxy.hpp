#ifndef IPLUGINPROXY_HPP
#define IPLUGINPROXY_HPP

#include <memory>
#include <vector>
#include <string>

#include "iplugin.hpp"

class IPluginProxy {
public:
    virtual bool init(std::vector<std::shared_ptr<IPlugin>> plugins) = 0;

    virtual std::string proxyId() const = 0;
};

#endif
