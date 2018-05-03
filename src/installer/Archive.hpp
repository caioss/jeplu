#ifndef ARCHIVE_HPP
#define ARCHIVE_HPP

#include <memory>
#include <cstdint>
#include <string>

// enum ARCHIVE_SUPPORTED
//     {
//         A_ZIP = 0,
//         A_RAR,
//     };

class Archive
{
public:

    /**
     * \brief Archive
     *
     */
    Archive(void) {};

    /**
     * \brief Archive
     *
     * \param archivePath Description of archivePath
     * \param pluginPath Description of pluginPath
     * \return Archive
     */
    Archive(const std::string &archivePath,
            const std::string &pluginPath);

    /**
     * \brief makeArchive
     *
     * \param  Description of
     * \return std::unique_ptr
     */
    static std::unique_ptr<Archive> makeArchive(void);

    /**
     * \brief make_archive
     *
     * \param archivePath Description of archivePath
     * \param pluginPath Description of pluginPath
     * \return std::unique_ptr
     */
    static std::unique_ptr<Archive> makeArchive(const std::string &archivePath,
                                                const std::string &pluginPath);

    /**
     * \brief setArchivePath
     *
     * \param archivePath Description of archivePath
     */
    virtual void setArchivePath(const std::string &archivePath) = 0;

    /**
     * \brief setPluginPath
     *
     * \param pluginPath Description of pluginPath
     */
    virtual void setPluginPath(const std::string &pluginPath) = 0;

    /**
     * \brief compress
     *
     * \param  Description of
     */
    virtual bool compress(void) = 0;

    /**
     * \brief decompress
     *
     * \param  Description of
     */
    virtual bool decompress(void) = 0;

    /**
     * \brief ~Archive
     *
     */
    virtual ~Archive(void);

protected:

    /**
     * \brief
     *
     */
    std::string _archivePath;

    /**
     *  \brief
     *
     */
    std::string _pluginPath;
};

#endif // ARCHIVE_HPP

