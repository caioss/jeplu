#ifndef IPLUGINFACTORY_H
#define IPLUGINFACTORY_H

#include "IPlugin.hpp"
#include "IPluginLoader.hpp"

#include <memory>
#include <string>
#include <vector>

/**
 *  The \c IPluginFactory interface represents a plugin factory that can be registered to the \c \sa PluginManager.
 *
 *  The objective of this interface is:
 *    - to provide ways to register \c \sa IPluginLoader;
 *    - create and store \c IPlugin object references.
 */
class IPluginFactory
{
public:
    /**
     *  \brief Search inside \c pluginsPath for dynamic libraries that are compatibles with any \c IPluginLoader
     *  registered.
     *
     *  For a given path, the \c IPluginFactory will search for available dynamic libraries and create (using the
     *  \c IPluginLoader) a \c IPlugin object for each library.
     *
     *  \param pluginsPaths The root path for dynamic library search.
     *  \return returns 0 if all the plugins were created succesfully. Otherwise, returns a negative number.
     */
    virtual int createPlugins(const std::vector<std::string> &pluginsPaths) = 0;

    /**
     *  \brief Gets a vector containing all the \c IPlugin references loaded.
     *
     *  \sa createPlugins()
     *
     *  \return Returns a vector with \c IPlugin shared objects.
     */
    virtual std::vector<std::shared_ptr<IPlugin>> getPlugins() const = 0;

    /**
     *  \brief Register \c IPluginLoader that can load its dynamic libraries.
     *
     *  If some lib cannot be dynamically linked to the application using this loader, another one will be called for
     *  the job.
     *  See \c \sa IPluginLoader for details.
     *
     *  \param loader The \c IPluginLoader reference that will be registered to this factory.
     *  \return Returns \c true if the \c loader could be registered sucessfully.
     */
    virtual bool registerLoader(std::shared_ptr<IPluginLoader> loader) = 0;
};

#endif
