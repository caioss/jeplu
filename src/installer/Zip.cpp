#include <cstring>
#include <iostream>

#include <QString>
#include <QDebug>
#include <QDirIterator>

#include "Zip.hpp"

Zip::Zip(void)
: Archive()
{
    _za = nullptr;
    _zf = nullptr;
}

void Zip::setFilePath(const std::string &filePath)
{
    _filePath = filePath;
}

void Zip::setPluginPath(const std::string &pluginPath)
{
    _pluginPath = pluginPath;
}

bool Zip::compress(void)
{
    if (_createZip())
    {
        if(_buildZip() == ZIP_SUCCESS)
        {
            return true;
        }
    }
    return false;
}

bool Zip::decompress(void)
{
    if (_openZip())
    {
        if (_extractZip() == ZIP_SUCCESS)
        {
            return true;
        }
    }
    return false;
}

bool Zip::_openZip(void)
{
    int err;

    if ((_za = zip_open(_filePath.c_str(), ZIP_CHECKCONS, &err)) != nullptr)
    {
        return true;
    }
    return false;
}

bool Zip::_createZip(void)
{
    int err;

    if ((_za = zip_open(_filePath.c_str(), ZIP_CREATE | ZIP_TRUNCATE, &err)) != nullptr)
    {
        return true;
    }
    return false;
}

void Zip::_closeZip(void)
{
    zip_error_t *zerr;

    if (_za != nullptr)
    {
        if (zip_close(_za) > 0)
        {
            zerr = zip_get_error(_za);
            qDebug() << zerr->zip_err;
        }
        _za = nullptr;
    }
}

bool Zip::_openFile(const std::string &filePath)
{
    // create and append
    _file.open(filePath,
               std::ofstream::out |
               std::ofstream::app |
               std::ofstream::binary);

    return _file.is_open();
}

uint8_t Zip::_writeFile(const std::string &filePath)
{
    // auxiliary memory chunk
    char mem_chunk[ZIP_MEM_CHUNK_SIZE];

    // libzip types
    zip_uint64_t sum = 0,
                 len = 0;

    if (!_openFile(filePath))
    {
        return ZIP_ERROR_FOPEN;
    }

    // clean buffer, avoid errors
    memset((void *)mem_chunk, 0, ZIP_MEM_CHUNK_SIZE);

    // read and save
    while (sum != _sb.size)
    {
        if ((len = zip_fread(_zf, (void *)mem_chunk, ZIP_MEM_CHUNK_SIZE)) < 0)
        {
            return ZIP_ERROR_READ;
        }
        _file.write(mem_chunk, (std::streamsize)len);
        sum += len;
    }
    _file.close();

    return ZIP_SUCCESS;
}

void Zip::_closeFile(void)
{
    _file.close();
}

uint8_t Zip::_extractZip(void)
{
    // limit and interator libzip related
    zip_int64_t num_entries = zip_get_num_entries(_za, ZIP_FL_COMPRESSED),
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
        if ((ret = _extractFile(i)) != ZIP_SUCCESS)
        {
            return ret;
        }
    }
    return ZIP_SUCCESS;
}

uint8_t Zip::_extractFile(const zip_int64_t index)
{
    // full filePath where will be save the archive
    std::string filePath;

    // len for zip_state.name (libc)
    size_t len = 0;

    // get zip stats
    if (zip_stat_index(_za, index, 0, &(_sb)) < 0)
    {
        return ZIP_ERROR_STAT;
    }

    // _file name len
    len      = strlen(_sb.name);
    filePath = _pluginPath + _sb.name;

    // if is a directory, create (so dependent)
    if ((_sb.name[len - 1] == '/') ||
        (_sb.name[len - 1] == '\\'))
    {
        return _mkdir(filePath);
    }

    if (!(_zf = zip_fopen_index(_za, index, 0)))
    {
        return ZIP_ERROR_FOPEN;
    }
    return _writeFile(filePath);
}

uint8_t Zip::_mkdir(const std::string &dirName)
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

bool Zip::_zipOpen(void)
{
    if (_za == nullptr)
    {
        if (!_openZip())
        {
            return false;
        }
    }
    return true;
}

uint8_t Zip::_zipAddFile(const std::string &filePath)
{
    zip_source_t *zs;

    if (_zipOpen())
    {
        if ((zs = zip_source_file(_za, filePath.c_str(), 0, 0)) != nullptr)
        {
            if (zip_file_add(_za, filePath.c_str(), zs, ZIP_FL_OVERWRITE) >= 0)
            {
                _closeZip();
                return ZIP_SUCCESS;
            }
            return ZIP_ERROR_FILE;
        }
        return ZIP_ERROR_SOURCE;
    }
    return ZIP_ERROR_OPEN;
}

uint8_t Zip::_zipAddDir(const std::string &dirPath)
{
    if (_zipOpen())
    {
        if (zip_dir_add(_za, dirPath.c_str(), ZIP_FL_ENC_UTF_8) >= 0)
        {
            _closeZip();
            return ZIP_SUCCESS;
        }
        return ZIP_ERROR_DIR;
    }
    return ZIP_ERROR_OPEN;
}

uint8_t Zip::_buildZip(void)
{
    QDirIterator dirIt(QString::fromStdString(_pluginPath),
                       QDirIterator::Subdirectories);

    //uint8_t ret = ZIP_SUCCESS;

    while(dirIt.hasNext())
    {
        // work on next dirIt
        dirIt.next();

        if (dirIt.fileInfo().isDir())
        {
            if (_zipAddDir(dirIt.filePath().toStdString()) != ZIP_SUCCESS)
            {
                return ZIP_ERROR_DIR;
            }
        }
        else if (dirIt.fileInfo().isFile())
        {
            if (_zipAddFile(dirIt.filePath().toStdString()) != ZIP_SUCCESS)
            {
                return ZIP_ERROR_FILE;
            }
        }
        else
        {
            continue;
        }
    }
    return ZIP_SUCCESS;
}

Zip::~Zip(void)
{
    _closeZip();
}

