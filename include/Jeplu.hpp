#ifndef JEPLU_HPP
#define JEPLU_HPP

#include "IPluginProxy.hpp"

// MSVC needs these specifications to export and import a class or function to/from a dll.
// see: https://msdn.microsoft.com/en-us/library/dabb5z75.aspx
#ifdef _WIN32
    #ifdef JEPLU_EXPORTS
        // If marked to export, mark as dllexport to MSVC mark a symbol as exported from a DLL.
        #define JEPLULIB_API __declspec(dllexport)
    #else
        // If not marked to export, use dllimport to import that exported symbol to another file.
        #define JEPLULIB_API __declspec(dllimport)
    #endif
#else
    #define JEPLULIB_API
#endif

/**
 *  \brief Indicates all the errors that \c Jeplu can return.
 */
enum class JepluErrs
{
    OK = 0, /*!< Successful. */
    INIT_FACTORY_ERR = -1, /*!< Indicates that the \c IPluginFactory could not be initialized. */
    INIT_MANAGER_ERR = -2  /*!< Indicates that the \c IPluginManager could not be initialized. */
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
class JEPLULIB_API Jeplu
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
    JepluErrs init(const std::string &pluginsRootPath);

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

private:
    /**
     *  \brief Define the private implementation of jeplu as Pimpl.
     */
    class JepluImpl;

    /**
     *  \brief Holds a unique pointer to the implementation Jeplu class.
     */
    std::unique_ptr<JepluImpl> _impl;
};

#endif // JEPLU_HPP
