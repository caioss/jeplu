#ifndef PLUGINMANAGER_H
#define PLUGINMANAGER_H

#include "ILibFinder.hpp"
#include "IPluginManager.hpp"
#include "PluginFactory.hpp"

#include <map>

/**
 *  \brief The \c PluginManager class creates and manage \c IPlugin.
 *
 *  The objective of this class is provide an easy management and cast of \c IPlugin objects. So given a path where
 *  dynamic libraries can be found, the \c PluginManager will try to find and load any dynamic library, creating a
 *  \c IPlugin object for each one.
 *
 *  The \c IPlugin object can be converted to a custom object by inheriting an interface supported by any
 *  \c IPluginProxy, that can be created and registered outside this module.
 *
 *  \sa IPlugin
 *  \sa IPluginProxy
 *  \sa IPluginFactory
 */
class PluginManager : public IPluginManager
{
public:
    /**
     *  \brief Default constructor.
     */
    PluginManager();

    /**
     *  \brief Initializes the \c PluginManager.
     *
     *  Creates all plugins that can be found in \c path and register them to its \c IPluginProxy.
     *
     *  \param path The path to look for dynamic libraries.
     *  \return Returns \c true if this \c PluginManager could be initialized. Otherwise, returns \c false.
     */
    bool init(const ILibFinder &finder);

    /**
     *  \brief Register the factory that will create the plugin objects.
     *
     *  If no factory is registered no plugins can be created, so this class became useless.
     *
     *  \param factory A shared reference to the \c IPluginFactory object.
     *  \return Returns \c true if the \c factory could be registered succesfully. Otherwise, returs true.
     */
    bool registerFactory(std::shared_ptr<IPluginFactory> factory);

    bool registerProxy(std::shared_ptr<IPluginProxy> proxy) override;

private:
    /**
     *  \brief Initializes all \c IPluginProxy available in \c _proxyList.
     */
    void _initializeProxies();

    /**
     *  \brief Adds all loaded plugins to its respective \c IPluginProxy.
     */
    void _addPluginsToProxies();

    /**
     *  \brief _factory The reference of a \c IPluginFactory object.
     */
    std::shared_ptr<IPluginFactory> _factory;

    /**
     *  \brief _proxyList Holds \c IPluginProxy object references and its IDs as keys.
     */
    std::map<std::string, std::shared_ptr<IPluginProxy>> _proxyList;
};

#endif
