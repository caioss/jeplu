#include "DlLoader.hpp"
#include "dlplugincreator.h"

#include <sys/types.h>
#include <cstring>
#include <dirent.h>
#include <errno.h>
#include <iostream>
#include <dlfcn.h>

DLLoader::DLLoader()
{

}

int DLLoader::_loadPlugin(const std::string &file, std::shared_ptr<IPlugin> &plugin)
{
    char *error;
    void *plugin_h = dlopen (file.c_str(), RTLD_LAZY);

    if (!plugin_h) {
        std::cout << "Failed to load plugin: " << dlerror() << std::endl;
        return -1;
    }

    create_t* create_plugin = (create_t*) dlsym(plugin_h, "create");

    if ((error = dlerror()) != NULL)  {
        std::cout << "Failed to sync plugin: " << error << std::endl;
        dlclose(plugin_h);
        return -2;
    }

    plugin = create_plugin();
    if (plugin) {
        plugin->plugin("plugins/");
    } else {
        dlclose(plugin_h);
        return -3;
    }

    return 0;
}

int DLLoader::loadPlugin(const std::string &pluginPath, std::shared_ptr<IPlugin> &plugin)
{
    int rc = _loadPlugin(pluginPath, plugin);

    return rc;
}
