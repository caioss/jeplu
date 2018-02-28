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

    int plugin(const std::string &pluginWorkingPath) Q_DECL_OVERRIDE;

    std::string pluginName() const Q_DECL_OVERRIDE;

    std::string pluginId() const Q_DECL_OVERRIDE;

    int pluginVersion() const Q_DECL_OVERRIDE;

    bool customFunction() override;
};

#endif
