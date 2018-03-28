#include <iostream>
#include <memory>
#include <string.h>
#include <vector>

#include "custom-proxy/ICustomInterface.hpp"
#include "custom-proxy/QCustomProxy.hpp"
#include "Jeplu.hpp"

int main(int argc, const char **argv)
{
    std::string pluginsPath;
    pluginsPath += "plugins/";

    std::cout << "Searching for plugins in " << pluginsPath << std::endl;

    Jeplu pluginManager;
    std::shared_ptr<QCustomProxy> proxy = std::make_shared<QCustomProxy>();
    pluginManager.registerProxy(proxy);
    pluginManager.init(pluginsPath);

    if (proxy->initialized())
    {
        for (std::weak_ptr<ICustomInterface> wPlugin : proxy->interfaces())
        {
            std::shared_ptr<ICustomInterface> plugin = wPlugin.lock();
            if (plugin)
            {
                std::cout << "Loading custom function from plugin " << plugin->pluginName() << std::endl;
                plugin->customFunction();
            }
        }
    }
    return 0;
}
