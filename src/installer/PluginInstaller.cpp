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
    _artifact = Artifact::make_artifact();

    if (_artifact != nullptr)
    {
        _artifact->setPluginPath(_pluginPath);
        _artifact->setFilePath(_filePath);

        if (_artifact->compress())
        {
            return true;
        }
    }
    return false;
}

bool PluginInstaller::installPlugin(void)
{
    // if (_artifact->open())
    // {
    //     if (_artifact->decompress())
    //     {
    //         _artifact->close();
    //         return true;
    //     }
    // }
    // return false;
}

PluginInstaller::~PluginInstaller(void)
{
}

