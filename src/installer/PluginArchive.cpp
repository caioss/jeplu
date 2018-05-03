#include <iostream>

#include "PluginArchive.hpp"

bool PluginArchive::exportPlugin(const std::string &archivePath,
                                 const std::string &pluginPath)
{
    _archive = Archive::makeArchive(archivePath, pluginPath);

    if (_archive != nullptr)
    {
        if (_archive->compress())
        {
            return true;
        }
    }
    return false;
}

bool PluginArchive::extractPlugin(const std::string &archivePath,
                                  const std::string &pluginPath)
{
    _archive = Archive::makeArchive(archivePath, pluginPath);

    if (_archive != nullptr)
    {
        if (_archive->decompress())
        {
            return true;
        }
    }
    return false;
}

