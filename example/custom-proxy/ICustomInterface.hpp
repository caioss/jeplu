#ifndef ICUSTOMINTERFACE_HPP
#define ICUSTOMINTERFACE_HPP

#include "IQtPlugin.hpp"

#define QCUSTOMINTERFACE_IID "qcustomproxy.proxy.jeplu"

class ICustomInterface : public virtual IPlugin
{
public:
    virtual int plugin(const std::string &pluginWorkingPath) Q_DECL_OVERRIDE = 0;

    virtual std::string pluginName() const Q_DECL_OVERRIDE = 0;

    virtual std::string pluginId() const Q_DECL_OVERRIDE = 0;

    virtual int pluginVersion() const Q_DECL_OVERRIDE = 0;

    std::string proxyId() const Q_DECL_OVERRIDE { return QCUSTOMINTERFACE_IID; }

    virtual bool customFunction() { return false; };
};

#endif
