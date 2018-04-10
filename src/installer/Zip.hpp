#ifndef _ZIP_H
#define _ZIP_H

#include <string>
#include <cstdint>
#include <fstream>

#include <zip.h>
#include <zipconf.h>

/**
 * \brief size of memory chunk, used to read the decompressed files.
 *
 */
#define ZIP_MEM_CHUNK_SIZE 64

//using namespace std;

/**
 * \brief Zip class, this class will handle zip archives.
 *
 */
class Zip {

public:
    /**
     * \brief Default Zip constructor.
     *
     */
    Zip();

    /**
     * \brief Zip constructor.
     *
     * @param m_pluginsPath std::string, file system plugins path.
     */
    Zip(std::string pluginsPath);

    /**
     * \brief Zip destructor.
     *
     */
    ~Zip();

    /**
     * \brief Sets the pluuginsPath attribute.
     *
     * @param pluginsPath std::string, file system plugins path.
     */
    void setPluginsPath(std::string pluginsPath);

    /**
     * \brief Opens the zip archive.
     *
     * @param zipPath std::string, zip archive file system path.
     * @return bool
     */
    bool openZip(const std::string zipPath);

    /**
     * \brief Closes zip archive.
     *
     */
    void closeZip(void);

    /**
     * \brief Extract the zip archive in the plugins path.
     *
     * The plugins path must be defined in another layer(module).
     *
     * @return ZIP_RET_VALUES
     */
    uint8_t extractZip(void);

    /**
     * \brief return values for zip related methods.
     *
     */
    enum ZIP_RET_VALUES
    {
        ZIP_SUCCESS = 0,
        ZIP_ERROR_OPEN,
        ZIP_ERROR_CLOSE,
        ZIP_ERROR_STAT,
        ZIP_ERROR_READ,
        ZIP_ERROR_ENTRIES,
        ZIP_ERROR_DIR,
    };

private:
    /**
     * \brief _mkdir, create the directory.
     *
     * @param  dirName std::string, directory name
     * @return uint8, ZIP_RET_VALUES
     */
    uint8_t _mkdir(const std::string dirName);

    /**
     * \brief Open/create file.
     *
     * @param  filePath std::string, file path.
     * @return bool
     */
    bool _openFile(const std::string filePath);

    /**
     * \brief Close the file.
     *
     */
    void _closeFile(void);

    /**
     * \brief _write, write the bytes read from the zip archive into the target file.
     *
     * @param path std::string, the file path.
     * @return uint8_t, ZIP_RET_VALUES
     */
    uint8_t _writeFile(const std::string filePath);

    /**
     * \brief _extracFile, extract the file from zip archive.
     *
     *
     * @param index Description of index
     * @return uint8_t, ZIP_RET_VALUES
     */
    uint8_t _extracFile(zip_int64_t index);

    /**
     * \brief Plugins path, where the plugins will be installed.
     *
     */
    std::string m_pluginsPath;

    /**
     * \brief ofstream
     *
     */
    std::ofstream m_file;

    /**
     * \brief pointer to struct zip, libzip related.
     *
     */
    zip_t *_za = nullptr;

    /**
     * \brief pointer to struct zip_file, libzip related.
     *
     */
    zip_file_t *_zf = nullptr;

    /**
     * \brief struct zip_stat, libzip related.
     *
     */
    zip_stat_t _sb;
};

#endif // _ZIP_H

