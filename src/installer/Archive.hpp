#ifndef ARCHIVE_HPP
#define ARCHIVE_HPP

#include <memory>
#include <cstdint>
#include <string>

// enum ARTIFACT_TYPE
//     {
//         AT_ZIP = 0,
//         AT_RAR,
//     };

class Archive
{
public:

    /**
     * \brief Archive
     *
     * \param  Description of
     * \return Archive
     */
    Archive(void);

    /**
     * \brief make_artifact
     *
     * \param at Description of at
     * \return Archive
     */
    static std::unique_ptr<Archive> make_archive(void);

    /**
     * \brief setFilePath
     *
     * \param filePath Description of filePath
     */
    virtual void setFilePath(const std::string &filePath) = 0;

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

    virtual ~Archive(void);

protected:
    std::string _filePath;

    std::string _pluginPath;
};

#endif // ARCHIVE_HPP

