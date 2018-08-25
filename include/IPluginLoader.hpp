#ifndef IPLUGINLOADER_H
#define IPLUGINLOADER_H

#include "IPlugin.hpp"

#include <memory>
#include <string>
#include <vector>

/**
 *  \brief The enum LoadingErrors indicates possible errors when tring to load a plugin.
 */
enum class LoadingErrs
{
    OK = 0,                /*!< Successful */
    LIB_NOT_LOADABLE = -1, /*!< The given lib couldn't be loaded. */
    OBJ_NOT_CASTABLE = -2, /*!< The given lib doesn't have a castable object. It can be lead by incompatible
                                versions. */
    CANT_CREATE_OBJ  = -3,  /*!< The given lib could not provide a object. */
    UNKNOW_ERROR     = -4   /*!< An unknown error occurred, not loading the lib. */
};

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
     *  \brief Default destructor.
     */
    virtual ~IPluginLoader() {}

    /**
     *  \brief Load all the plugins from a given \c path.
     *
     *  All the succesfully loaded plugins will be appended to \c plugins.
     *
     *  \param path The path where all the libraries will be loaded.
     *  \param plugin[out] A shared reference to the new \c IPlugin object. If the plugin cannot be loaded, it's setted
     *  to nullptr.
     *
     *  \return Returns an error specified at \c \sa LoadingErrors.
     */
    virtual LoadingErrs loadPlugin(const std::string &pluginPath, std::shared_ptr<IPlugin> &plugin) = 0;

    /**
     *  \brief Gets the name of the loader.
     *  \return The loader's name.
     */
    virtual std::string name() const = 0;

    /**
     *  \brief Gets the last error described.
     *  \return A string describing the last error.
     */
    virtual std::string errString() const = 0;
};

#endif
