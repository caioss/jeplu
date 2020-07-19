#ifndef ARCHIVE_HPP
#define ARCHIVE_HPP

#include <memory>
#include <cstdint>
#include <string>

class Archive
{
public:
    /**
     * \brief Default constructor.
     *
     */
    Archive() {};

    /**
     * \brief Alternative constructor.
     *
     * \param archivePath Archive path.
     * \param pluginPath  Plugin path.
     */
    Archive(const std::string &archivePath, const std::string &pluginPath);

    /**
     * \brief Creates the proper archive object.
     *
     * \return Archive object.
     */
    static std::unique_ptr<Archive> makeArchive();

    /**
     * \brief Creates the proper archive object.
     *
     * \param archivePath Archive path.
     * \param pluginPath Plugin path.
     * \return Archive object.
     */
    static std::unique_ptr<Archive> makeArchive(const std::string &archivePath, const std::string &pluginPath);

    /**
     * \brief Set the archive path.
     *
     * \param archivePath Archive path.
     */
    virtual void setArchivePath(const std::string &archivePath) = 0;

    /**
     * \brief Set the plugin path.
     *
     * \param pluginPath Plugin path.
     */
    virtual void setPluginPath(const std::string &pluginPath) = 0;

    /**
     * \brief Compress the plugin.
     *
     */
    virtual bool compress() = 0;

    /**
     * \brief Decompresses the plugin.
     *
     */
    virtual bool decompress() = 0;

    /**
     * \brief Destructor.
     *
     */
    virtual ~Archive();

protected:
    /**
     * \brief Archive path.
     */
    std::string _archivePath;

    /**
     *  \brief Plugin path.
     */
    std::string _pluginPath;
};

#endif // ARCHIVE_HPP

