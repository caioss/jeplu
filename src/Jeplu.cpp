#include "Jeplu.hpp"

#ifdef __linux__
    #include "DlLoader.hpp"
#endif
#include "PluginManager.hpp"
#include "PluginFactory.hpp"
#include "QtLoader.hpp"
#include "JepluLibFinder.hpp"

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

bool Jeplu::JepluImpl::initFactory()
{
    bool ret = false;
    _factory = std::make_shared<PluginFactory>();

    // Register DLLoader if it's a linux system.
#ifdef __linux__
    std::shared_ptr<DLLoader> dlLoader = std::make_shared<DLLoader>();
    ret |= _factory->registerLoader(std::dynamic_pointer_cast<IPluginLoader>(dlLoader));
#endif
    // Register QtLoader
    std::shared_ptr<QtLoader> qLoader = std::make_shared<QtLoader>();
    ret |= _factory->registerLoader(std::dynamic_pointer_cast<IPluginLoader>(qLoader));

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

    std::unique_ptr<ILibFinder> libFinder = (finder != nullptr ?
                                             std::move(finder) :
                                             std::unique_ptr<JepluLibFinder>(new JepluLibFinder(pluginsRootPath))
    );
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
