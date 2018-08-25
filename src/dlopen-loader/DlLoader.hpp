#ifndef DLLOADER_H
#define DLLOADER_H

#include "IPluginLoader.hpp"

class DLLoader : public IPluginLoader
{
public:
    DLLoader();

    LoadingErrs loadPlugin(const std::string &pluginPath, std::shared_ptr<IPlugin> &plugin) override;

    std::string name() const override { return "Dl Loader"; }

    std::string errString() const override;

private:
    /**
     *  \brief Try to load the lib file \c file and cast to a known Plugin object.
     */
    LoadingErrs _loadPlugin(const std::string &file, std::shared_ptr<IPlugin> &plugin);

    /**
     *  \brief Holds the last error string.
     */
    std::string _errStr;
};

#endif
