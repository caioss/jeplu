#ifndef QCUSTOMPROXY_HPP
#define QCUSTOMPROXY_HPP

#include "IPluginProxy.hpp"

class QCustomProxy : public IPluginProxy
{
private:
    /**
     *  \brief Indicates if this proxy is initialized.
     */
    bool _initialized;

    std::vector<std::weak_ptr<IPlugin>> _plugins;

public:
    QCustomProxy();

    ~QCustomProxy();

    bool init(std::vector<std::weak_ptr<IPlugin>> plugins = std::vector<std::weak_ptr<IPlugin>>()) override;

    std::string proxyId() const override;

    bool initialized() const override;

    std::vector<std::weak_ptr<IPlugin>> getPlugins() const override;

    bool addPlugin(std::weak_ptr<IPlugin> plugin) override;
};

#endif
