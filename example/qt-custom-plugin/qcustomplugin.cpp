#include "qcustomplugin.hpp"

#include <QDebug>

QCustomPlugin::QCustomPlugin()
{
}

int QCustomPlugin::plugin(const std::string &pluginWorkingPath)
{
    qDebug() << "QCustomPlugin loaded!";
    return 0;
}

std::string QCustomPlugin::pluginName() const
{
    return "QCustomPlugin";
}

std::string QCustomPlugin::pluginId() const
{
    return QCUSTOM_PLUGIN_ID;
}

int QCustomPlugin::pluginVersion() const
{
    return 1;
}

bool QCustomPlugin::customFunction()
{
    qDebug() << "Custom function works!";

    return true;
}
