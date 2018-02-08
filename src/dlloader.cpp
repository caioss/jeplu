#include "dlloader.hpp"

#include <sys/types.h>
#include <cstring>
#include <dirent.h>
#include <errno.h>
#include <iostream>
#include <dlfcn.h>

DLLoader::DLLoader()
{

}

std::vector<std::string> DLLoader::_getFiles(const std::string &path)
{
    DIR *dp;
    struct dirent *dirp;
    std::vector<std::string> files;
    if((dp  = opendir(path.c_str())) == NULL) {
        return files;
    }

    while ((dirp = readdir(dp)) != NULL) {
        if (strcmp(dirp->d_name, "..") && strcmp(dirp->d_name, ".")) {
            std::string dirName = path + "/" + std::string(dirp->d_name);
            files.push_back(dirName);
            std::cout << "Find file:" << dirName << std::endl;
        }
    }
    closedir(dp);
    return files;
}

int DLLoader::_loadPlugin(const std::string &file, IPlugin* plugin)
{
    void *plugin_h;
    char *error;

    plugin_h = dlopen (file.c_str(), RTLD_LAZY);
    if (!plugin_h) {
        std::cout << "Failed to load plugin: " << dlerror() << std::endl;
        return -1;
    }

    create_t* create_plugin = (create_t*) dlsym(plugin_h, "create");

    if ((error = dlerror()) != NULL)  {
        std::cout << "Failed to sync plugin: " << error << std::endl;
        return -2;
    }

    plugin = create_plugin();
    if (plugin) {
        plugin->plugin();
    } else {
        plugin = nullptr;
    }
    dlclose(plugin_h);

    return 0;
}

std::vector<std::string> DLLoader::loadPlugins(const std::vector<std::string> &pluginsPaths,
                                               std::vector<std::shared_ptr<IPlugin>> &plugins)
{
    std::cout << "Loading plugins..." << std::endl;
    std::vector<std::string> failedPaths;
    // Find files
    for(std::string pluginPath : pluginsPaths) {
        std::shared_ptr<IPlugin*> plugin;
        int rc = _loadPlugin(file, plugin);
        if (rc == 0) {
            plugins.push_back(plugin);
        } else {
            failedPaths.push_back(pluginPath);
        }
    }

    return failedPaths;
}
