#ifndef QCUSTOMPROXY_HPP
#define QCUSTOMPROXY_HPP

#include "IPluginAdapter.hpp"

class ICustomInterface;

class QCustomAdapter : public IPluginAdapter
{
public:
    QCustomAdapter();

    ~QCustomAdapter();

    bool init(std::vector<std::weak_ptr<IPlugin>> plugins = std::vector<std::weak_ptr<IPlugin>>()) override;

    std::string adapterId() const override;

    bool initialized() const override;

    bool hasPluginsLoaded() const override;

    std::vector<std::weak_ptr<IPlugin>> plugins() const override;

    bool addPlugin(std::weak_ptr<IPlugin> plugin) override;

    /**
     *  \brief Retrieve all plugins as custom interfaces.
     */
    std::vector<std::weak_ptr<ICustomInterface>> interfaces() const;

private:
    /**
     *  \brief Indicates if this proxy is initialized.
     */
    bool _initialized;

    std::vector<std::weak_ptr<IPlugin>> _plugins;
};

#endif
