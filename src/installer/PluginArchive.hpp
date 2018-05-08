#ifndef PLUGIN_ARCHIVE_HPP
#define PLUGIN_ARCHIVE_HPP

#include <string>
#include <memory>

#include "Archive.hpp"

/**
 *  The class PluginArchive, manages the plugin archive.
 *
 *  The objective of this class is:
 *    - provide a interface to export/extract plugins.
 */
class PluginArchive
{
public:
    /**
     * \brief Default constructor.
     *
     */
    PluginArchive(void){};

    /**
     * \brief Create a archive from a plugin directory.
     *
     * \param archivePath Archive path.
     * \param pluginPath  Plugin path.
     * \return bool
     */
    bool exportPlugin(const std::string &archivePath,
                      const std::string &pluginPath);

    /**
     * \brief Extract the archive contents to a plugin directory.
     *
     * \param archivePath Archive path.
     * \param pluginPath  Plugin path.
     * \return bool
     */
    bool extractPlugin(const std::string &archivePath,
                       const std::string &pluginPath);

    /**
     * \brief Destructor.
     *
     */
    ~PluginArchive(void) {};

private:

    /**
     * \brief Archive interface pointer.
     *
     */
    std::unique_ptr<Archive> _archive;
};

#endif // PLUGIN_ARCHIVE_HPP

