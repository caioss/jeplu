#ifndef DLLOADER_H
#define DLLOADER_H

#include "ipluginloader.hpp"

class DLLoader : public IPluginLoader
{
private:
    std::vector<std::string> _getFiles(const std::string &path);

    int _loadPlugin(const std::string &file, IPlugin* plugin);

public:
    DLLoader();

    std::vector<std::string> loadPlugins(const std::vector<std::string> &pluginsPath,
                                         std::vector<std::shared_ptr<IPlugin>> &plugins) override;

    std::string name() const override { return "Dl Loader"; }
};

#endif
