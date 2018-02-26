#ifndef DLLOADER_H
#define DLLOADER_H

#include "ipluginloader.hpp"

class DLLoader : public IPluginLoader
{
private:
    int _loadPlugin(const std::string &file, std::shared_ptr<IPlugin> &plugin);
    
public:
    DLLoader();

    int loadPlugin(const std::string &pluginPath, std::shared_ptr<IPlugin> &plugin) override;

    std::string name() const override { return "Dl Loader"; }
};

#endif
