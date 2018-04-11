#include <cstring>
#include <iostream>

#include <QDir>
#include <QString>

#include "Zip.hpp"

Zip::Zip()
{
    this->_za = nullptr;
    this->_zf = nullptr;
}

Zip::Zip(std::string pluginPath)
{
    this->_za = nullptr;
    this->_zf = nullptr;
    this->_pluginPath = pluginPath;
}

void Zip::setPluginPath(std::string pluginPath)
{
    this->_pluginPath = pluginPath;
}

bool Zip::openZip(const std::string zipFile)
{
    int err;

    if ((this->_za = zip_open(zipFile.c_str(), ZIP_CHECKCONS | ZIP_RDONLY, &err)) != nullptr)
    {
        return true;
    }
    return false;
}

void Zip::closeZip(void)
{
    if (this->_za != nullptr)
    {
        zip_close(this->_za);
    }
}

bool Zip::_openFile(const std::string filePath)
{
    // create and append
    this->m_file.open(filePath,
                      std::ofstream::out |
                      std::ofstream::app |
                      std::ofstream::binary);

    return this->m_file.is_open();
}

void Zip::_closeFile(void)
{
    this->m_file.close();
}

uint8_t Zip::extractZip(void)
{
    // limit and interator libzip related
    zip_int64_t num_entries = zip_get_num_entries(this->_za, ZIP_FL_COMPRESSED),
                i;

    // auxiliary
    uint8_t ret;

    // verify numbers of entries in the zip archive
    if (num_entries < 0)
    {
        return ZIP_ERROR_ENTRIES;
    }

    // extract all the contents from zip archive
    for (i = 0; i < num_entries; i++)
    {
        if ((ret = this->_extracFile(i)) != ZIP_SUCCESS)
        {
            return ret;
        }
    }
    return ZIP_SUCCESS;
}

uint8_t Zip::_extracFile(zip_int64_t index)
{
    // full filePath where will be save the archive
    std::string filePath;

    // len for zip_state.name (libc)
    size_t len = 0;

    // get zip stats
    if (zip_stat_index(this->_za, index, 0, &(this->_sb)) < 0)
    {
        return ZIP_ERROR_STAT;
    }

    // this->m_file name len
    len      = strlen(this->_sb.name);
    filePath = this->_pluginPath + this->_sb.name;

    // if is a directory, create (so dependent)
    if (this->_sb.name[len - 1] == '/')
    {
        return this->_mkdir(filePath);
    }

    if (!(this->_zf = zip_fopen_index(this->_za, index, 0)))
    {
        return ZIP_ERROR_OPEN;
    }
    return this->_writeFile(filePath);
}

uint8_t Zip::_writeFile(const std::string filePath)
{
    // auxiliary memory chunk
    char mem_chunk[ZIP_MEM_CHUNK_SIZE];

    // libzip types
    zip_uint64_t sum = 0,
                 len = 0;

    if (!this->_openFile(filePath))
    {
        return ZIP_ERROR_OPEN;
    }

    // clean buffer, avoid errors
    memset((void *)mem_chunk, 0, ZIP_MEM_CHUNK_SIZE);

    // read and save
    while (sum != this->_sb.size)
    {
        if ((len = zip_fread(this->_zf, (void *)mem_chunk, ZIP_MEM_CHUNK_SIZE)) < 0)
        {
            return ZIP_ERROR_READ;
        }
        this->m_file.write(mem_chunk, (std::streamsize)len);
        sum += len;
    }
    this->_closeFile();

    // success
    return ZIP_SUCCESS;
}

uint8_t Zip::_mkdir(const std::string dirName)
{
    // QDir object
    QDir dir;

    // dir path as a qt string
    const QString dirPath = QString::fromStdString(dirName);

    // create directory
    if (dir.mkdir(dirPath))
    {
        return ZIP_SUCCESS;
    }
    return ZIP_ERROR_DIR;
}

Zip::~Zip()
{
    this->closeZip();
}

