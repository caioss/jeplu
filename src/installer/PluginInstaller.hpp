#ifndef _PLUGIN_INSTALLER_HPP
#define _PLUGIN_INSTALLER_HPP

#include <string>
#include <memory>

#include "Artifact.hpp"

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
    PluginInstaller(void);

    /**
     * \brief setPluginPath
     *
     * @param pluginPath Description of pluginPath
     */
    void setPluginPath(const std::string pluginPath);

    /**
     * \brief setZipFile
     *
     * @param zipFile Description of zipFile
     */
    void setFilePath(const std::string filePath);

    /**
     * \brief init
     *
     * @param  Description of
     */
     bool init(void);

    /**
     * \brief installPlugin
     *
     * @param  Description of
     * @return bool
     */
    bool installPlugin(void);

    bool exportPlugin(void);

    /**
     * \brief PluginInstaller destructor.
     *
     */
    ~PluginInstaller(void);

private:
    /**
     * \brief brief description
     *
     * @param name description
     *
     */
    std::string _pluginPath;

    /**
     * \brief brief description
     *
     * @param name description
     *
     */
    std::string _filePath;

    /**
     * \brief brief description
     *
     * @param name description
     *
     */
    //std::unique_ptr<Ab> _zip;
    std::unique_ptr<Artifact> _artifact;
};

#endif // _PLUGIN_INSTALLER_HPP

