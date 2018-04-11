#ifndef _PLUGIN_INSTALLER_HPP
#define _PLUGIN_INSTALLER_HPP

#include <string>
#include <memory>

#include "Zip.hpp"
#include "Jeplu.hpp"

/**
 * \brief This class is resposble for install the plugin
 *
 */
class PluginInstaller
{
public:
    /**
     * \brief PluginInstaller constructor.
     *
     */
    PluginInstaller(std::string pluginPath = std::string(),
                    std::string zipFile    = std::string());

    /**
     * \brief setPluginPath
     *
     * @param pluginPath Description of pluginPath
     */
    void setPluginPath(std::string pluginPath);

    void setZipFile(std::string zipFile);

    void init(void);

    bool installPlugin(void);

    /**
     * \brief PluginInstaller destructor.
     *
     */
     ~PluginInstaller();

protected:
private:
    std::string _pluginPath;

    std::string _zipFile;

    std::unique_ptr<Zip> _zip;
};

#endif // _PLUGIN_INSTALLER_HPP

