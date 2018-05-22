#include "Archive.hpp"
#include "Zip.hpp"

Archive::~Archive()
{
}

Archive::Archive(const std::string &archivePath, const std::string &pluginPath) :
_archivePath (archivePath),
_pluginPath (pluginPath)
{
}

std::unique_ptr<Archive> Archive::makeArchive()
{
    std::unique_ptr<Archive> archive;

    archive.reset(new Zip());

    return archive;
}

std::unique_ptr<Archive> Archive::makeArchive(const std::string &archivePath, const std::string &pluginPath)
{
    std::unique_ptr<Archive> archive;

    archive.reset(new Zip(archivePath, pluginPath));

    return archive;
}

