#include "QtLoader.hpp"
#include "IQtPlugin.hpp"

#include <QDebug>
#include <QPluginLoader>
#include <QString>

QtLoader::QtLoader() :
_errStr("No error.")
{
}

int QtLoader::loadPlugin(const std::string &pluginPath, std::shared_ptr<IPlugin> &plugin)
{
    int rc = LoadingErrors::OK;
    QPluginLoader loader(QString::fromStdString(pluginPath));
    if (loader.load())
    {
        IPlugin *castPlugin = qobject_cast<IPlugin*>(loader.instance());
        if (castPlugin != nullptr)
        {
            plugin.reset(castPlugin);
            _errStr = "Success";
        }
        else
        {
            _errStr = "Unable to cast the library object to a known object.";
            rc = LoadingErrors::OBJ_NOT_CASTABLE;
        }
    }
    else
    {
        _errStr = loader.errorString().toStdString();
        rc = LoadingErrors::LIB_NOT_LOADABLE;
    }

    return rc;
}

std::string QtLoader::errString() const
{
    return _errStr;
}
