#include "Archive.hpp"
#include "Zip.hpp"

Archive::Archive(const std::string &archivePath,
                 const std::string &pluginPath)
{
    _archivePath = archivePath;
    _pluginPath  = pluginPath;
}

std::unique_ptr<Archive> Archive::makeArchive(void)
{
    std::unique_ptr<Archive> archive;

    archive.reset(new Zip());

    //artifact = std::unique_ptr<Zip>();

    return archive;
}

std::unique_ptr<Archive> Archive::makeArchive(const std::string &archivePath,
                                              const std::string &pluginPath)
{
    std::unique_ptr<Archive> archive;

    archive.reset(new Zip(archivePath, pluginPath));

    //artifact = std::unique_ptr<Zip>();

    return archive;
}

Archive::~Archive(void)
{
}

