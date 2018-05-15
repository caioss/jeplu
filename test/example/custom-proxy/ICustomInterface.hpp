#ifndef ICUSTOMINTERFACE_HPP
#define ICUSTOMINTERFACE_HPP

#include "IQtPlugin.hpp"

static const char* customInterfaceID = "qcustomproxy.proxy.jeplu";

class ICustomInterface : public virtual IPlugin
{
public:
    virtual int plugin(const std::string &pluginWorkingPath) override = 0;

    virtual std::string pluginName() const override = 0;

    virtual std::string pluginId() const override = 0;

    virtual int pluginVersion() const override = 0;

    std::string proxyId() const override { return customInterfaceID; }

    virtual bool customFunction() { return false; };
};

#endif
