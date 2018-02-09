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

std::string QCustomPlugin::pluginName()
{
    return "QCustomPlugin";
}

std::string QCustomPlugin::pluginGroup()
{
    return "";
}

int QCustomPlugin::pluginVersion()
{
    return 1;
}
