#ifndef QTLOADER_H
#define QTLOADER_H

#include <memory>
#include <QList>
#include <QFile>

#include "ipluginloader.hpp"

class QtLoader : public IPluginLoader
{
private:
    QList<QFile> _getFiles(const std::string &path);

    int _loadPlugin(const QString &filePath, std::shared_ptr<IPlugin> plugin);

public:
    QtLoader();

    std::vector<std::string> loadPlugins(const std::vector<std::string> &pluginsPath,
                                         std::vector<std::shared_ptr<IPlugin>> &plugins) override;

    std::string name() const override { return "Qt Loader"; }
};

#endif // QTLOADER_H
