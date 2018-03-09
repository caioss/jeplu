#ifndef JEPLU_HPP
#define JEPLU_HPP

#include "IPluginProxy.hpp"
#include "PluginManager.hpp"

/**
 *  \brief The Jeplu is the main class that works as a facade for dynamic libraries (plugins) management.
 *
 *  With this class it`s possible to load and retrieve plugins that match with the registered proxies.`
 *
 *  To use this class, the caller should register an \c IPluginProxy. After the proxy registration, the class can be
 *  initialized and all the plugins availabe in the given path that matches with any proxy will be loaded and be ready
 *  to be access and casted by its proxy.
 *
 *  \sa IPluginProxy
 *  \sa IPlugin
 */
class Jeplu
{
public:
    /**
     *  \brief Default constructor.
     */
    Jeplu();

    /**
     *  \brief Initializes the class loading all the plugin available in \c pluginsRootPath.
     *
     *  This class shoulb be called after any proxy registration, otherwise it won't be recognized.
     */
    int init(const std::string &pluginsRootPath);

    /**
     *  \brief Registers a \c IPluginProxy object to Jeplu.
     *
     *  After the initialization of this class, if the proxy is already registered, all the plugins will be available
     *  in the \c IPluginProxy that it matches with.
     *  \param param A shared object of  \c IPluginProxy.
     *  \return Returns \c true if the \c proxy could be registered. Otherwise, returns \c false.
     */
    bool registerProxy(std::shared_ptr<IPluginProxy> proxy);

    // template <typename T> int pluginsWithInterface(std::vector<std::weak_ptr<T>> &plugins) {} //TODO

    // template <typename T> std::vector<std::string> pluginsID() const {} //TODO

private:
    bool _initFactory();

    bool _initProxies();

    std::unique_ptr<PluginManager> _manager;
};

#endif // JEPLU_HPP
