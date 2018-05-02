#include <iostream>

#include "PluginInstaller.hpp"

PluginInstaller::PluginInstaller(void)
{
}

void PluginInstaller::setPluginPath(const std::string pluginPath)
{
    _pluginPath = pluginPath;
}

void PluginInstaller::setFilePath(const std::string filePath)
{
    _filePath = filePath;
}

bool PluginInstaller::init(void)
{
    _archive = Archive::make_archive();

    if (_archive != nullptr)
    {
        _archive->setPluginPath(_pluginPath);
        _archive->setFilePath(_filePath);

        if (_archive->compress())
        {
            return true;
        }
    }
    return false;
}

bool PluginInstaller::installPlugin(void)
{
    // if (_archive->open())
    // {
    //     if (_archive->decompress())
    //     {
    //         _archive->close();
    //         return true;
    //     }
    // }
    // return false;
}

PluginInstaller::~PluginInstaller(void)
{
}

