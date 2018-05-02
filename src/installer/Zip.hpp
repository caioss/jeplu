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
     * \param  Description of
     * \return Zip
     */
    Zip(void);

    /**
     * \brief setFilePath
     *
     * \param filePath Description of filePath
     */
    void setFilePath(const std::string &filePath);

    /**
     *  \brief function description
     *
     *  Detailed description
     *
     *  \param param
     *  \return return type
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
     * \brief Zip
     *
     * \param  Description of
     */
    ~Zip(void);

private:
    /**
     * \brief Opens the zip archive.
     *
     * \param zipPath std::string, zip archive file system path.
     * @return bool
     */
    bool _openZip(void);

    /**
     *
     *
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
     * \brief close
     *
     * \param  Description of
     */
    void _closeZip(void);

    /**
     * \brief _openFile
     *
     * \param  Description of
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
     * \brief _closeFile
     *
     * \param  Description of
     */
    void _closeFile(void);

    /**
     * \brief _mkdir
     *
     * \param dirName Description of dirName
     * \return uint8_t
     */
    uint8_t _mkdir(const std::string &dirName);

    uint8_t _buildZip(void);

    bool _zipOpen(void);

    uint8_t _zipAddFile(const std::string &filePath);

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

