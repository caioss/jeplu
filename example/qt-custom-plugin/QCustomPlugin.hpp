#ifndef QCUSTOMPLUGIN_H
#define QCUSTOMPLUGIN_H

#include "ICustomInterface.hpp"

#include <QObject>
#include <string.h>

#define QCUSTOM_PLUGIN_ID "com.jeplu.plugins.qcustomplugin"

class QCustomPlugin : public QObject, public ICustomInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID QCUSTOM_PLUGIN_ID)
    Q_INTERFACES(IPlugin)

public:
    QCustomPlugin();

    ~QCustomPlugin() {}

    int plugin(const std::string &pluginWorkingPath) override;

    std::string pluginName() const override;

    std::string pluginId() const override;

    int pluginVersion() const override;

    bool customFunction() override;
};

#endif
