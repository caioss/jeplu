#ifndef QTLOADER_H
#define QTLOADER_H

#include <memory>
#include <QList>
#include <QFile>

#include "ipluginloader.hpp"

class QtLoader : public IPluginLoader
{
public:
    QtLoader();

    int loadPlugin(const std::string &pluginPath, std::shared_ptr<IPlugin> &plugin) override;

    std::string name() const override { return "Qt Loader"; }
};

#endif // QTLOADER_H
