#ifndef IPLUGINLOADER_H
#define IPLUGINLOADER_H

#include <memory>
#include <string>
#include <vector>

#include "iplugin.hpp"

/**
 *  @brief The IPluginLoader interface represents a \c IPlugin loader.
 *
 *  This class should load all libs from a given path and transform it to a list of \c IPlugin objects. More
 *  than one \c IPluginLoader can be registered. If some lib cannot be dynamically linked to the application
 *  using this loader, another one will be called for the job.
 *
 *  @sa IPlugin
 */
class IPluginLoader
{
public:
    /**
     * @brief Load all the plugins from a given \c path.
     *
     * All the succesfully loaded plugins will be appended to \c plugins.
     * @param path The path where all the libraries will be loaded.
     * @param plugins[out] The vector containing a list of plugins. All the loaded plugins will be appended to this
     * vector.
     * @return A list of paths to the lib files that were not loaded.
     */
    virtual int loadPlugin(const std::string &pluginPath, std::shared_ptr<IPlugin> &plugins) = 0;

    /**
     * @brief Gets the name of the loader.
     * @return The loader's name.
     */
    virtual std::string name() const = 0;
};

#endif
