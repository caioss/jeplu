#include "Jeplu.hpp"

#include "PluginManager.hpp"
#include "PluginFactory.hpp"

// Check if DlLoader should be added.
#if defined(__linux__) && !defined(NO_DL_LOADER)
    #define USE_DL_LOADER
    #include "DlLoader.hpp"
#endif

// Check if QtLoader should be added.
#ifndef NO_QT_LOADER
    #include "QtLoader.hpp"
#endif

// Check if Default libfinder is selected.
#ifndef NO_DEFAULT_LIBFINDER
    #include "JepluLibFinder.hpp"
#endif

#include <iostream>
#include <memory>

/**
 *  \brief Implements and defines the JepluImpl as Pimpl.
 */
class Jeplu::JepluImpl
{
public:
    /**
     *  \brief Default constructor.
     */
    JepluImpl();

    /**
     *  \brief Initializes the PluginFactory and set it up to the Plugin Manager.
     */
    bool initFactory();

    /**
     *  \brief Initializes the plugin manager.
     */
    bool initManager(std::unique_ptr<ILibFinder> finder);

    /**
     *  \brief Register the given adapter into PluginManager.
     */
    bool registerAdapter(std::shared_ptr<IPluginAdapter> adapter);

    /**
     *  \brief Register the given adapter into PluginManager.
     */
    bool registerLoader(std::unique_ptr<IPluginLoader> adapter);

    /**
     *  \brief Indicates if any \c IPlugin was loaded into any \c IPluginAdapter succesfully.
     */
    bool hasLoadedPlugins() const;

private:
    /**
     *  \brief Holds a unique pointer to PluginManager.
     */
    std::unique_ptr<PluginManager> _manager;

    /**
     *  \brief Holds a shared pointer to PluginFactory.
     */
    std::shared_ptr<PluginFactory> _factory;
};

// JepluImpl implementation

Jeplu::JepluImpl::JepluImpl() :
_manager(new PluginManager()), _factory(new PluginFactory())
{}

bool Jeplu::JepluImpl::initFactory()
{
    bool ret = false;

#ifdef USE_DL_LOADER
    // Register DLLoader if it's a linux system and it's marked for build.
    std::shared_ptr<DLLoader> dlLoader = std::make_shared<DLLoader>();
    ret |= _factory->registerLoader(std::dynamic_pointer_cast<IPluginLoader>(dlLoader));
#endif

#ifndef NO_QT_LOADER
    // Register QtLoader if marked for build.
    std::shared_ptr<QtLoader> qLoader = std::make_shared<QtLoader>();
    ret |= _factory->registerLoader(std::dynamic_pointer_cast<IPluginLoader>(qLoader));
#endif

    // Register factory
    ret &= _manager->registerFactory(_factory);
    return ret;
}

bool Jeplu::JepluImpl::initManager(std::unique_ptr<ILibFinder> finder)
{
    return _manager->init(std::move(finder));
}

bool Jeplu::JepluImpl::registerAdapter(std::shared_ptr<IPluginAdapter> adapter)
{
    return _manager->registerAdapter(adapter);
}

bool Jeplu::JepluImpl::registerLoader(std::unique_ptr<IPluginLoader> loader)
{
    return _factory->registerLoader(std::move(loader));
}

bool Jeplu::JepluImpl::hasLoadedPlugins() const
{
    return _manager->hasLoadedPlugins();
}

// Jeplu Implementation

// Tell the compiler to generate default special members which utilize the power of std::unique_ptr.
// We must do it here because the implementation class is defined at this point thus std::unique_ptr
// can properly handle the implementation pointer.
Jeplu::~Jeplu() = default;

Jeplu::Jeplu() :
_impl(new JepluImpl())
{}

JepluErrs Jeplu::init(const std::string &pluginsRootPath, std::unique_ptr<ILibFinder> finder)
{
    std::cout << "[JEPLU] Initializing Jeplu..." << std::endl;
    JepluErrs rc = JepluErrs::OK;
    // Initializes and register factory to manager.
    if (!_impl->initFactory())
    {
        std::cout << "[JEPLU] The Plugin Factory could not be initialized or there are no loader available." << std::endl;
        return JepluErrs::INIT_FACTORY_ERR;
    }

    std::unique_ptr<ILibFinder> libFinder(nullptr);

    // Initializes libFinder with JepluLibFinder if it was not excluded for build.
#ifndef NO_DEFAULT_LIBFINDER
    libFinder = std::unique_ptr<JepluLibFinder>(new JepluLibFinder(pluginsRootPath));
#endif

    // If a finder is provided, use it.
    if (finder)
    {
        libFinder = std::move(finder);
    }

    if (!_impl->initManager(std::move(libFinder)))
    {
        std::cout << "[JEPLU] Plugin Manager couldn't be initialized." << std::endl;
        rc = JepluErrs::INIT_MANAGER_ERR;
    }
    return rc;
}

bool Jeplu::hasLoadedPlugins() const
{
    return _impl->hasLoadedPlugins();
}

bool Jeplu::registerAdapter(std::shared_ptr<IPluginAdapter> adapter)
{
    return _impl->registerAdapter(adapter);
}

bool Jeplu::registerLoader(std::unique_ptr<IPluginLoader> loader)
{
    return _impl->registerLoader(std::move(loader));
}
