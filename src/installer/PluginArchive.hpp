#ifndef PLUGIN_ARCHIVE_HPP
#define PLUGIN_ARCHIVE_HPP

#include <string>
#include <memory>

#include "Archive.hpp"

/**
 * \brief This class is resposble for install the plugin
 *
 */
class PluginArchive
{
public:
    /**
     * \brief PluginArchive constructor.
     *
     */
    PluginArchive(void){};

    /**
     * \brief exportPlugin
     *
     * \param archivePath Description of archivePath
     * \param pluginPath Description of pluginPath
     * \return bool
     */
    bool exportPlugin(const std::string &archivePath,
                      const std::string &pluginPath);

    /**
     * \brief extractPlugin
     *
     * \param archivePath Description of archivePath
     * \param pluginPath Description of pluginPath
     * \return bool
     */
    bool extractPlugin(const std::string &archivePath,
                       const std::string &pluginPath);

    /**
     * \brief PluginArchive destructor.
     *
     */
    ~PluginArchive(void);

private:

    /**
     * \brief brief description
     *
     * @param name description
     *
     */
    std::unique_ptr<Archive> _archive;
};

#endif // PLUGIN_ARCHIVE_HPP

