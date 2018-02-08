#include "qtloader.hpp"

#include <QDebug>

QtLoader::QtLoader()
{

}

QList<QFile> QtLoader::_getFiles(const std::string &path)
{
    QList<QFile> files;

    // ...

    return files;
}

int QtLoader::_loadPlugin(const QString &filePath, std::shared_ptr<IPlugin> plugin)
{
    plugin = nullptr;

    return -1;
}

std::vector<std::string> QtLoader::loadPlugins(const std::vector<std::string> &pluginsPath,
                                               std::vector<std::shared_ptr<IPlugin>> &plugins)
{
    qDebug() << "Loading qt plugins...";
    std::vector<std::string> failedPaths;
    // Find files
    for(std::string pluginPath : pluginsPath) {
        std::shared_ptr<IPlugin> plugin;
        int rc = _loadPlugin(QString::fromStdString(pluginPath), plugin);
        if (rc == 0) {
            plugins.push_back(plugin);
        } else {
            failedPaths.push_back(pluginPath);
        }
    }

    return failedPaths;
}
