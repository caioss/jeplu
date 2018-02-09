#ifndef QCUSTOMPLUGIN_H
#define QCUSTOMPLUGIN_H

#include "iqtplugin.hpp"

#include <QObject>
#include <string.h>

class QCustomPlugin : public QObject, public IPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "com.jeplu.plugins.qcustomplugin")
    Q_INTERFACES(IPlugin)
    
public:
    QCustomPlugin();

    ~QCustomPlugin() {}

    int plugin(const std::string &pluginWorkingPath) Q_DECL_OVERRIDE;

    std::string  pluginName() Q_DECL_OVERRIDE;

    int pluginVersion() Q_DECL_OVERRIDE;

    std::string pluginGroup() Q_DECL_OVERRIDE;
};

#endif
