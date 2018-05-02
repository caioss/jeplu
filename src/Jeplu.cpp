#include "Jeplu.hpp"

#ifdef __linux__
    #include "DlLoader.hpp"
#endif
#include "PluginManager.hpp"
#include "PluginFactory.hpp"
#include "QtLoader.hpp"
#include "JepluLibFinder.hpp"

#include <iostream>

/**
 *  \brief Implements and defines the JepluImpl as Pimpl.
 */
class Jeplu::JepluImpl
{
public:
    /**
     *  \brief Default constructor.
     */
    JepluImpl() :
    _manager(new PluginManager())
    {}

    /**
     *  \brief Initializes the PluginFactory and set it up to the Plugin Manager.
     */
    bool initFactory();

    /**
     *  \brief Initializes the plugin manager.
     */
    bool initManager(const JepluLibFinder &finder);

    /**
     *  \brief Register the given proxy into PluginManager.
     */
    bool registerProxy(std::shared_ptr<IPluginProxy> proxy);

    /**
     *  \brief Indicates if any \c IPlugin was loaded into any \c IPluginProxy succesfully.
     */
    bool hasLoadedPlugins() const;

private:
    /**
     *  \brief Holds a unique pointer to PluginManager.
     */
    std::unique_ptr<PluginManager> _manager;
};

// JepluImpl implementation

bool Jeplu::JepluImpl::initFactory()
{
    bool ret = false;
    std::shared_ptr<PluginFactory> pluginFactory = std::make_shared<PluginFactory>();

// Register DLLoader if it's a linux system.
#ifdef __linux__
    std::shared_ptr<DLLoader> dlLoader = std::make_shared<DLLoader>();
    ret |= pluginFactory->registerLoader(std::dynamic_pointer_cast<IPluginLoader>(dlLoader));
#endif
    // Register QtLoader
    std::shared_ptr<QtLoader> qLoader = std::make_shared<QtLoader>();
    ret |= pluginFactory->registerLoader(std::dynamic_pointer_cast<IPluginLoader>(qLoader));

    // Register factory
    ret &= _manager->registerFactory(pluginFactory);
    return ret;
}

bool Jeplu::JepluImpl::initManager(const JepluLibFinder &finder)
{
    return _manager->init(finder);
}

bool Jeplu::JepluImpl::registerProxy(std::shared_ptr<IPluginProxy> proxy)
{
    return _manager->registerProxy(proxy);
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

int Jeplu::init(const std::string &pluginsRootPath)
{
    std::cout << "Initializing Jeplu..." << std::endl;
    int rc = 0;
    // Initializes and register factory to manager.
    if (!_impl->initFactory())
    {
        std::cout << "The Plugin Factory could not be initialized or there are no loader available." << std::endl;
        return JepluErrs::INIT_FACTORY_ERR;
    }

    JepluLibFinder finder(pluginsRootPath);
    if (!_impl->initManager(finder))
    {
        std::cout << "Plugin Manager couldn't be initialized." << std::endl;
        rc = JepluErrs::INIT_MANAGER_ERR;
    }
    return rc;
}

bool Jeplu::hasLoadedPlugins() const
{
    return _impl->hasLoadedPlugins();
}

bool Jeplu::registerProxy(std::shared_ptr<IPluginProxy> proxy)
{
    return _impl->registerProxy(proxy);
}
