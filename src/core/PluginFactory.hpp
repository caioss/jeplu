#ifndef PLUGINFACTORY_H
#define PLUGINFACTORY_H

#include "IPluginLoader.hpp"

#include <memory>

/**
 *  The class \c PluginFactory represents a plugin factory that can register loaders and create plugins with the
 *  registered loaders.
 *
 *  The objective of this class is:
 *    - to provide ways to register \c \sa IPluginLoader;
 *    - create and store \c IPlugin object references.
 */
class PluginFactory
{
public:
    /**
     *  \brief Default constructor.
     */
    PluginFactory();

     /**
     *  \brief Search inside each path in \c pluginsPath for a dynamic library that are compatible with any
     *  \c IPluginLoader registered.
     *
     *  For each path, the \c PluginFactory will search for available dynamic libraries and create (using the
     *  \c IPluginLoader) a \c IPlugin object for each library.
     *
     *  If some lib cannot be dynamically linked to the application using some loader, another one will be called for
     *  the job, if available.
     *
     *  \param path The root path to find the dynamic libraries.
     *  \return Returns >= 0 when success and < 0 when it fails. The errors represents:
     *          \c 1 If no plugins were loaded.
     *          \c -0 if all the plugins were created succesfully;
     *          \c -1 if no loader is avilable.
     */
    int createPlugins(const std::vector<std::string> &pluginsPaths);

    /**
     *  \brief Indicates if any \c IPlugin was created.
     */
    bool hasPlugins() const;

    /**
     *  \brief Gets a vector containing all the \c IPlugin references loaded.
     *
     *  \sa createPlugins()
     *
     *  \return Returns a vector with \c IPlugin shared objects.
     */
    std::vector<std::shared_ptr<IPlugin>> plugins() const;

    /**
     *  \brief Register \c IPluginLoader that can load its dynamic libraries.
     *
     *  See \c \sa IPluginLoader for details.
     *
     *  \param loader The \c IPluginLoader reference that will be registered to this factory.
     *  \return Returns \c true if the \c loader could be registered sucessfully.
     */
    bool registerLoader(std::shared_ptr<IPluginLoader> loader);

private:
    /**
     *  \brief _plugins Holds all \c IPlugin references createdd by \c createPlugins().
     */
    std::vector<std::shared_ptr<IPlugin>> _plugins;

    /**
     *  \brief _loaders Holds all loaders registered by \c registerLoader().
     */
    std::vector<std::shared_ptr<IPluginLoader>> _loaders;
};

#endif
