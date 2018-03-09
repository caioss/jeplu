#include "DlLoader.hpp"
#include "dlplugincreator.h"

#include <sys/types.h>
#include <cstring>
#include <dirent.h>
#include <errno.h>
#include <iostream>
#include <dlfcn.h>

DLLoader::DLLoader() :
_errStr("No error")
{
}

int DLLoader::_loadPlugin(const std::string &file, std::shared_ptr<IPlugin> &plugin)
{
    char *error;
    void *plugin_h = dlopen (file.c_str(), RTLD_LAZY);

    if (!plugin_h)
    {
        _errStr = "Failed to load plugin: " + std::string(dlerror());
        return IPluginLoader::LIB_NOT_LOADABLE;
    }

    create_t *create_plugin = (create_t*) dlsym(plugin_h, "create");

    if ((error = dlerror()) != NULL)
    {
        _errStr = "Failed to sync plugin: " + std::string(error);
        dlclose(plugin_h);
        return IPluginLoader::OBJ_NOT_CASTABLE;
    }

    plugin = create_plugin();
    if (plugin)
    {
        _errStr = "Success";
        plugin->plugin("plugins/");
    }
    else
    {
        _errStr = "Unable to create a plugin object.";
        dlclose(plugin_h);
        return IPluginLoader::CANT_CREATE_OBJ;
    }

    return 0;
}

DLLoader::LoadingErrors DLLoader::loadPlugin(const std::string &pluginPath, std::shared_ptr<IPlugin> &plugin)
{
    LoadingErrors rc = static_cast<LoadingErrors>(_loadPlugin(pluginPath, plugin));

    return rc;
}

std::string DLLoader::errString() const
{
    return _errStr;
}
