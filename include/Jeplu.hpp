#ifndef JEPLU_HPP
#define JEPLU_HPP

#ifdef _WIN32
    #define LIB_EXPORT __declspec(dllexport)
#else
    #define LIB_EXPORT
#endif

#include "IPluginProxy.hpp"

namespace JepluErrs
{
    enum JepluErrs
    {
        OK = 0,
        INIT_FACTORY_ERR = -1,
        INIT_MANAGER_ERR = -2
    };
};

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
class LIB_EXPORT Jeplu
{
public:
    /**
     *  \brief Default constructor.
     */
    Jeplu();

    /**
     *  \brief Default destructor.
     */
    ~Jeplu();

    /**
     *  \brief Initializes the class loading all the plugin available in \c pluginsRootPath.
     *
     *  This class shoulb be called after any proxy registration, otherwise it won't be recognized.
     *
     *  \param pluginsRootPath The root path where all the plugins will be located.
     *
     *  \return Returns 0 if succeded. Otherwise, returns a negative error, described in \c JepluErrs.
     */
    int init(const std::string &pluginsRootPath);

    /**
     *  \brief Indicates if any plugin was loaded into any \c IPluginProxy registered.
     */
    bool hasLoadedPlugins() const;

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
    /**
     *  \brief Define the private implementation of jeplu as Pimpl.
     */
    class LIB_EXPORT JepluImpl;

    /**
     *  \brief Holds a unique pointer to the implementation Jeplu class.
     */
    std::unique_ptr<JepluImpl> _impl;
};

#endif // JEPLU_HPP
