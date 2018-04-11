#include "PluginInstaller.hpp"

PluginInstaller::PluginInstaller(std::string pluginPath, std::string zipFile)
    : _pluginPath(pluginPath),
      _zipFile(zipFile),
      _zip(nullptr)
{
}

void PluginInstaller::setPluginPath(std::string pluginPath)
{
    this->_pluginPath = pluginPath;
}

void PluginInstaller::setZipFile(std::string zipFile)
{
    this->_zipFile = zipFile;
}

void PluginInstaller::init(void)
{
    this->_zip.reset(new Zip());
    this->_zip->setPluginPath(this->_pluginPath);
}

bool PluginInstaller::installPlugin(void)
{
    if (this->_zip->openZip(this->_zipFile))
    {
        if (this->_zip->extractZip() == Zip::ZIP_SUCCESS)
        {
            return true;
        }
    }
    return false;
}

