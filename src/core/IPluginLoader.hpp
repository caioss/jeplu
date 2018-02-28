#ifndef IPLUGINLOADER_H
#define IPLUGINLOADER_H

#include "IPlugin.hpp"

#include <memory>
#include <string>
#include <vector>

/**
 *  \brief The IPluginLoader interface represents a \c IPlugin loader.
 *
 *  This class should load all libs from a given path and transform it to a list of \c IPlugin objects.
 *
 *  Note that each implementation of this interface should be built and linked statically so its dependecies does not
 *  impact the core of the project.
 *
 *  \sa IPlugin
 */
class IPluginLoader
{
public:
    /**
     *  \brief Load all the plugins from a given \c path.
     *
     *  All the succesfully loaded plugins will be appended to \c plugins.
     *
     *  \param path The path where all the libraries will be loaded.
     *  \param plugin[out] A shared reference to the new \c IPlugin object. If the plugin cannot be loaded, it's setted
     *  to nullptr.
     *
     *  \return Returns 0 if the plugin was loaded. Otherwise, returns a negative number representing an specific error.
     */
    virtual int loadPlugin(const std::string &pluginPath, std::shared_ptr<IPlugin> &plugin) = 0;

    /**
     *  \brief Gets the name of the loader.
     *  \return The loader's name.
     */
    virtual std::string name() const = 0;
};

#endif
