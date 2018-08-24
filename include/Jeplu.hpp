
#ifndef JEPLU_HPP
#define JEPLU_HPP

#include "jeplu_api.hpp"
#include "core/ILibFinder.hpp"

#include <memory>
#include <string>

class IPluginAdapter;
class IPluginLoader;
//class ILibFinder;

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
 *  Each \c IPlugin represents an object that can be built from a dynamic library. That object can represent pretty much
 *  anything, but only if a \c IPluginAdapter that accepts its type is registered to the Jeplu API. The \c IPluginLoader
 *  makes a dynamic library compatible with this API, finding the symbol that creates an object castable to \c IPlugin.
 *
 *  The \c IPluginAdapter represents an object capable of casting a \c IPlugin object to a custom type predefined by this
 *  adapter. In other works, the \c IPlugin subclass that you are creating must be also a subclass of an interface
 *  supported by a \c IPluginAdapter that you created for your application and registered to the Jeplu API.
 *  The link between the \c IPlugin and its \c IPluginAdapter is the adapter's id provided by your custom plugin.
 *
 *  The usage of this class is based on the \c IPluginAdapter and where the API will look for the dynamic libraries. So,
 *  the caller should register an \c IPluginAdapter and after the adapter registration, the class can be initialized and
 *  all the plugins availabe in the given path (under the rules of any \c ILibFinder , see \c JepluLibFinder for details
 *  of the default \c ILibFinder registered) that matches with any adapter will be loaded and be ready to be access and
 *  casted by its adapter.
 *
 *  By default, this API has an implementation for a \c IPluginLoader. You can find more detailed info in the file
 *  "include/IQtPlugin.hpp".
 *
 *  \sa IPluginAdapter
 *  \sa IPlugin
 *  \sa IPluginLoader
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
     *  This class shoulb be called after any adapter registration, otherwise it won't be recognized.
     *
     *  \param pluginsRootPath The root path where all the plugins will be located.
     *  \param finder An optional finder. If none is given, the default one is created.
     *         \sa ILibFinder
     *
     *  \return Returns 0 if succeded. Otherwise, returns a negative error, described in \c JepluErrs.
     */
    JepluErrs init(const std::string &pluginsRootPath, std::unique_ptr<ILibFinder> finder = nullptr);

    /**
     *  \brief Indicates if any plugin was loaded into any \c IPluginAdapter registered.
     */
    bool hasLoadedPlugins() const;

    /**
     *  \brief Registers a \c IPluginAdapter to Jeplu.
     *
     *  After the initialization of this class, if the adapter is already registered, all the plugins will be available
     *  in the \c IPluginAdapter that it matches with.
     *  \param param A shared object of  \c IPluginAdapter.
     *  \return Returns \c true if the \c adapter could be registered. Otherwise, returns \c false.
     */
    bool registerAdapter(std::shared_ptr<IPluginAdapter> adapter);

    /**
     *  \brief Registers a \c IPluginLoader to Jeplu.
     *
     *  \sa IPluginLoader
     *  \param param A unique ptr of \c IPluginLoader.
     *  \return Returns \c true if the \c loader could be registered. Otherwise, returns \c false.
     */
    bool registerLoader(std::unique_ptr<IPluginLoader> loader);

private:
    /**
     *  This class is non copyable.
     */
    Jeplu(Jeplu &);
    const Jeplu &operator=(const Jeplu &);

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
