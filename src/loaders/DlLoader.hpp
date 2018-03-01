#ifndef DLLOADER_H
#define DLLOADER_H

#include "IPluginLoader.hpp"

class DLLoader : public IPluginLoader
{
public:
    DLLoader();

    int loadPlugin(const std::string &pluginPath, std::shared_ptr<IPlugin> &plugin) override;

    std::string name() const override { return "Dl Loader"; }

private:
    int _loadPlugin(const std::string &file, std::shared_ptr<IPlugin> &plugin);
};

#endif
