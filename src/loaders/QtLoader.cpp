#include "QtLoader.hpp"
#include "IQtPlugin.hpp"

#include <QDebug>
#include <QPluginLoader>
#include <QString>

QtLoader::QtLoader()
{
}

QtLoader::LoadingErrors QtLoader::loadPlugin(const std::string &pluginPath, std::shared_ptr<IPlugin> &plugin)
{
    LoadingErrors rc = IPluginLoader::OK;
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
            rc = IPluginLoader::OBJ_NOT_CASTABLE;
        }
    }
    else
    {
        qDebug() << "QtLoader coudn't load the lib " << QString::fromStdString(pluginPath);
        qDebug() << loader.errorString();
        rc = IPluginLoader::LIB_NOT_LOADABLE;
    }

    return rc;
}
