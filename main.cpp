#include <iostream>
#include <memory>
#include <string.h>
#include <vector>

#include "src/pluginmanager.hpp"
#include "src/pluginfactory.hpp"
#include "src/qtloader.hpp"
#ifdef __linux__
    #include "src/dlloader.hpp"
#endif

int main(int argc, const char **argv)
{
    std::string pluginsPath;
    pluginsPath += "/plugins";

    std::cout << "Searching for plugins in " << pluginsPath << std::endl;

    // TODO: Create a Facade for this:
    std::shared_ptr<PluginFactory> pluginFactory = std::make_shared<PluginFactory>();
    std::vector<std::shared_ptr<IPluginLoader>> loaders;
#ifdef __linux__
    std::shared_ptr<DLLoader> dlLoader = std::make_shared<DLLoader>();
    loaders.push_back(std::dynamic_pointer_cast<IPluginLoader>(dlLoader));
#endif
    std::shared_ptr<QtLoader> qLoader = std::make_shared<QtLoader>();
    loaders.push_back(std::dynamic_pointer_cast<IPluginLoader>(qLoader));
    for (std::shared_ptr<IPluginLoader> loader : loaders) {
        if (pluginFactory->registerLoader(loader)) {
            std::cout << "Loader " << loader->name() << " registered." << std::endl;
        } else {
            std::cout << "Loader " << loader->name() << " couldn't be registered." << std::endl;
        }
    }

    PluginManager *pluginManager = new PluginManager();
    pluginManager->registerFactory(pluginFactory);
    pluginManager->init(pluginsPath);

    return 0;
}
