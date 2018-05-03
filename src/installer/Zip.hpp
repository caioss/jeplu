#ifndef ZIP_HPP
#define ZIP_HPP

#include <string>
#include <cstdint>
#include <fstream>

#include <zip.h>

#include "Archive.hpp"

/**
 * \brief size of memory chunk, used to read the decompressed files.
 */
#define ZIP_MEM_CHUNK_SIZE 64

enum ZIP_RET_VALUES
{
        ZIP_SUCCESS = 0,
        ZIP_ERROR_OPEN,
        ZIP_ERROR_FOPEN,
        ZIP_ERROR_CLOSE,
        ZIP_ERROR_STAT,
        ZIP_ERROR_READ,
        ZIP_ERROR_ENTRIES,
        ZIP_ERROR_DIR,
        ZIP_ERROR_SOURCE,
        ZIP_ERROR_FILE,
};

class Zip : public Archive
{
public:

    /**
     * \brief Zip
     *
     */
    Zip(void);

    /**
     * \brief Zip
     *
     * \param archivePath Description of archivePath
     * \param pluginPath Description of pluginPath
     * \return Zip
     */
    Zip(const std::string &archivePath,
        const std::string &pluginPath);

    /**
     * \brief setArchivePath
     *
     * \param archivePath Description of archivePath
     */
    void setArchivePath(const std::string &archivePath);

    /**
     * \brief setPluginPath
     *
     * \param pluginPath Description of pluginPath
     */
    void setPluginPath(const std::string &pluginPath);

    /**
     * \brief compress
     *
     * \param  Description of
     */
    bool compress(void);

    /**
     * \brief decompress
     *
     * \param  Description of
     */
    bool decompress(void);

    /**
     * \brief ~Zip
     *
     * \param  Description of
     */
    ~Zip(void);

private:

    /**
     * \brief _openZip
     *
     * \return bool
     */
    bool _openZip(void);

    /**
     * \brief _createZip
     *
     * \return bool
     */
    bool _createZip(void);

    /**
     * \brief _extractZip
     *
     * \param  Description of
     * \return uint8_t
     */
    uint8_t _extractZip(void);

    /**
     * \brief _closeZip
     *
     */
    void _closeZip(void);

    /**
     * \brief _openFile
     *
     * \param filePath Description of filePath
     * \return bool
     */
    bool _openFile(const std::string &filePath);

    /**
     * \brief _extracFile
     *
     * \param index Description of index
     * \return uint8_t
     */
    uint8_t _extractFile(const zip_int64_t index);

    /**
     * \brief _writeFile
     *
     * \param filePath Description of filePath
     * \return int8_t
     */
    uint8_t _writeFile(const std::string &filePath);

    /**
     * \brief _mkdir
     *
     * \param dirName Description of dirName
     * \return uint8_t
     */
    uint8_t _mkdir(const std::string &dirName);

    /**
     * \brief _buildZip
     *
     * \param  Description of
     * \return uint8_t
     */
    uint8_t _buildZip(void);

    /**
     * \brief _zipOpen
     *
     * \return bool
     */
    bool _zipOpen(void);

    /**
     * \brief _zipAddFile
     *
     * \param filePath Description of filePath
     * \return uint8_t
     */
    uint8_t _zipAddFile(const std::string &filePath);

    /**
     * \brief _zipAddDir
     *
     * \param dirPath Description of dirPath
     * \return uint8_t
     */
    uint8_t _zipAddDir(const std::string &dirPath);

    /**
     * \brief ofstream
     *
     */
    std::ofstream _file;

    /**
     * \brief pointer to struct zip, libzip related.
     *
     */
    zip_t *_za;

    /**
     * \brief pointer to struct zip_file, libzip related.
     *
     */
    zip_file_t *_zf;

    /**
     * \brief struct zip_stat, libzip related.
     *
     */
    zip_stat_t _sb;
};

#endif // ZIP_HPP

