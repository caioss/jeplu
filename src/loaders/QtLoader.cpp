#include "QtLoader.hpp"
#include "IQtPlugin.hpp"

#include <QDebug>
#include <QPluginLoader>
#include <QString>

QtLoader::QtLoader()
{
}

int QtLoader::loadPlugin(const std::string &pluginPath, std::shared_ptr<IPlugin> &plugin)
{
    int rc = 0;
    QPluginLoader loader(QString::fromStdString(pluginPath));
    if (loader.load())
    {
        IPlugin *castPlugin = qobject_cast<IPlugin*>(loader.instance());
        if (castPlugin != nullptr)
        {
            plugin.reset(castPlugin);
        }
        else
        {
            rc = -2;
        }
    }
    else
    {
        qDebug() << "QtLoader coudn't load the lib " << QString::fromStdString(pluginPath);
        qDebug() << loader.errorString();
        rc = -1;
    }

    return rc;
}
