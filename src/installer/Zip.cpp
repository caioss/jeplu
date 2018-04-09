// linux only
#include <sys/stat.h>

#include <cstring>
#include <iostream>

#include "Zip.hpp"

Zip::Zip()
{
}

Zip::Zip(string pluginsPath)
{
    this->m_pluginsPath = pluginsPath;
}

void Zip::setPluginsPath(string pluginsPath)
{
    this->m_pluginsPath = pluginsPath;
}

bool Zip::openZip(const string zipPath)
{
    int err;

    if ((this->m_za = zip_open(zipPath.c_str(),
                               ZIP_CHECKCONS | ZIP_RDONLY,
                               &err)) != NULL)
    {
        return true;
    }
    return false;
}

void Zip::closeZip(void)
{
    if (this->m_za != NULL)
    {
        zip_close(m_za);
    }
}

bool Zip::_openFile(const string filePath)
{
    // create and append
    this->m_file.open(filePath, ofstream::out | ofstream::app | ofstream::binary);

    return this->m_file.is_open();
}

void Zip::_closeFile(void)
{
    this->m_file.close();
}

uint8_t Zip::extractZip(void)
{
    // limit and interator libzip related
    zip_int64_t num_entries = zip_get_num_entries(this->m_za, ZIP_FL_COMPRESSED),
                i;

    // auxiliary
    uint8_t ret = -1;

    // verify numbers of entries in the zip archive
    if (num_entries < 0)
    {
        return ZIP_ERROR_ENTRIES;
    }

    // extract all the contents from zip archive this->m_file
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
    string filePath;

    // len for zip_state.name (libc)
    size_t len = 0;

    // get zip stats, TODO errors
    if (zip_stat_index(m_za, index, 0, &(this->m_sb)) < 0)
    {
        return ZIP_ERROR_STAT;
    }

    // this->m_file name len
    len      = strlen(this->m_sb.name);
    filePath = this->m_pluginsPath + this->m_sb.name;

    // if is a directory, create (so dependent)
    if (this->m_sb.name[len - 1] == '/')
    {
        return this->_mkdir(filePath, len);
    }

    if (!(this->m_zf = zip_fopen_index(this->m_za, index, 0)))
    {
        return ZIP_ERROR_OPEN;
    }
    return this->_writeFile(filePath);
}

uint8_t Zip::_writeFile(const string filePath)
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
    while (sum != this->m_sb.size)
    {
        if ((len = zip_fread(this->m_zf, (void *)mem_chunk, ZIP_MEM_CHUNK_SIZE)) < 0)
        {
            return ZIP_ERROR_READ;
        }
        this->m_file.write(mem_chunk, (streamsize)len);
        sum += len;
    }
    this->_closeFile();

    // success
    return ZIP_SUCCESS;
}

// ifdef windows?
uint8_t Zip::_mkdir(const string filePath, size_t len)
{
    // create directory
    if (mkdir(filePath.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH) < 0)
    {
        return ZIP_ERROR_DIR;
    }

    return ZIP_SUCCESS;
}

Zip::~Zip()
{
    this->closeZip();
}

// OBS
// plugins filePath no set, empty, another layer will verify this
// if ((this->m_pluginsPath.empty()))
//     return;

