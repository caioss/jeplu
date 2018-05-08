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

/**
 * \brief Zip return values.
 */
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

/**
 *  The class Zip manages the operations related to de zip file type.
 *
 *  The objective of this class is:
 *    - provide interaction with the zip file type.
 *    - operations supported: create, compress and decompress.
 */
class Zip : public Archive
{
public:

    /**
     * \brief Default constructor.
     */
    Zip(void);

    /**
     * \brief Alternative constructor.
     *
     * \param archivePath Archive path.
     * \param pluginPath  Plugin path.
     */
    Zip(const std::string &archivePath,
        const std::string &pluginPath);

    /**
     * \brief Set the archive path.
     *
     * \param archivePath Archive path.
     */
    void setArchivePath(const std::string &archivePath);

    /**
     * \brief Set the plugin path.
     *
     * \param pluginPath Plugin path.
     */
    void setPluginPath(const std::string &pluginPath);

    /**
     * \brief Compress the directory to a zip archive.
     *
     */
    bool compress(void);

    /**
     * \brief Decompress a zip archive.
     *
     */
    bool decompress(void);

    /**
     * \brief Destructor.
     *
     */
    ~Zip(void);

private:

    /**
     * \brief Open the zip archive.
     *
     * \return True on success, false otherwise.
     */
    bool _openZip(void);

    /**
     * \brief Create a zip archive.
     *
     * \return True on success, false otherwise.
     */
    bool _createZip(void);

    /**
     * \brief Extract zip archive contents.
     *
     */
    uint8_t _extractZip(void);

    /**
     * \brief Close zip archive.
     *
     */
    void _closeZip(void);

    /**
     * \brief Open a file in the virtual file system.
     *
     * \param filePath File path.
     * \return True on success, false otherwise.
     */
    bool _openFile(const std::string &filePath);

    /**
     * \brief Extract one file/directory from zip archive.
     *
     * \param index In the zip archive we have a array of files/directorys the index indicates which one.
     * \retval ZIP_SUCCESS      Success.
     * \retval ZIP_ERROR_FOPEN  It was not possible to open the virtual file system file.
     * \retval ZIP_ERROR_STAT   Insternal error from libzip zip_stat_index function.
     * \retval ZIP_ERROR_READ   It was not possible to read the compressed file.
     */
    uint8_t _extractFile(const zip_int64_t index);

    /**
     * \brief Write the contents decompressed in to the file in the virtual file system.
     *
     * \param filePath File path.
     * \retval ZIP_SUCCESS      Success.
     * \retval ZIP_ERROR_FOPEN  It was not possible to open the virtual file system file.
     * \retval ZIP_ERROR_READ   It was not possible to read the compressed file.
     */
    uint8_t _writeFile(const std::string &filePath);

    /**
     * \brief Creates a directory in the virtual file system.
     *
     * \param dirName Directory's name.
     * \retval ZIP_SUCCESS      Success.
     * \retval ZIP_ERROR_DIR    It was not possible to create the directory.
     */
    uint8_t _mkdir(const std::string &dirName);

    /**
     * \brief Build the zip archive.
     *
     * \retval ZIP_SUCCESS      Success.
     * \retval ZIP_ERROR_DIR    It was not possible to add the directory.
     * \retval ZIP_ERROR_FILE   It was not possible to add the file.
     */
    uint8_t _buildZip(void);

    /**
     * \brief Verifies if the zip archive is open.
     *
     * \return True on success, false otherwise.
     */
    bool _zipOpen(void);

    /**
     * \brief Add a file in the zip archive.
     *
     * \param filePath File path.
     * \retval ZIP_SUCCESSS    Success.
     * \retval ZIP_ERROR_OPEN  It was not possible to open zip archive.
     * \retval ZIP_ERROR_FILE  It was not possible to add the target file.
     */
    uint8_t _zipAddFile(const std::string &filePath);

    /**
     * \brief Add a directory in the zip archive.
     *
     * \param dirPath Directory path.
     * \retval ZIP_SUCCESSS    Directory added into zip archive.
     * \retval ZIP_ERROR_OPEN  It was not possible to open zip archive.
     * \retval ZIP_ERROR_DIR   It was not possible to add the target directory.
     */
    uint8_t _zipAddDir(const std::string &dirPath);

    /**
     * \brief ofstream var.
     */
    std::ofstream _file;

    /**
     * \brief pointer to struct zip, libzip related.
     */
    zip_t *_za;

    /**
     * \brief pointer to struct zip_file, libzip related.
     */
    zip_file_t *_zf;

    /**
     * \brief struct zip_stat, libzip related.
     */
    zip_stat_t _sb;
};

#endif // ZIP_HPP

