#include "Jeplu.hpp"

#ifdef __linux__
    #include "DlLoader.hpp"
#endif
#include "PluginManager.hpp"
#include "PluginFactory.hpp"
#include "QtLoader.hpp"
#include "JepluLibFinder.hpp"

#include <iostream>

Jeplu::Jeplu() :
_manager(std::unique_ptr<PluginManager>(new PluginManager()))
{}

bool Jeplu::_initFactory()
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

int Jeplu::init(const std::string &pluginsRootPath)
{
    std::cout << "Initializing Jeplu..." << std::endl;
    int rc = 0;
    // Initializes and register factory to manager.
    if (!_initFactory())
    {
        std::cout << "The Plugin Factory could not be initialized or there are no loader available." << std::endl;
        return -1;
    }

    JepluLibFinder finder(pluginsRootPath);
    if (!_manager->init(finder))
    {
        std::cout << "Plugin Manager couldn't be initialized." << std::endl;
        rc = -2;
    }
    return rc;
}

bool Jeplu::registerProxy(std::shared_ptr<IPluginProxy> proxy)
{
    return _manager->registerProxy(proxy);
}
